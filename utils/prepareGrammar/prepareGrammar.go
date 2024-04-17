package main

import (
	"encoding/json"
	"fmt"
	"log"
	"os"
)

type Rule struct {
	Name string
	Body []string
}

type Grammar struct {
	Rules        []Rule
	Terminals    []string
	NonTerminals []string
}

type Item struct {
	Rule

	Symbol string
	DotPos int
}

type Items []Item

type ItemsSet []Items

type Action struct {
	ActionType string
	NextState  int
	Rule       Rule
}

type CanonicalTableLR1 struct {
	Goto         map[int]map[string]int
	Action       map[int]map[string]Action
	StartState   int
	Terminals    []string
	NonTerminals []string
}

var (
	First        = map[string]map[string]struct{}{}
	GrammarMiniC Grammar

	dummy   struct{}
	dot     = "⦿"
	epsilon = "ε"

	nullRule = Rule{"NULL", []string{}}

	errAction = Action{
		ActionType: "error",
		NextState:  -1,
		Rule:       nullRule,
	}
)

func isTerminal(chr string) bool {
	for i := 0; i < len(GrammarMiniC.Terminals); i++ {
		if chr == GrammarMiniC.Terminals[i] {
			return true
		}
	}
	return false
}

func containsItem(Collection Items, newOne Item) bool {

CollectionLoop:
	for _, elem := range Collection {
		if elem.Name != newOne.Name ||
			elem.DotPos != newOne.DotPos ||
			elem.Symbol != newOne.Symbol ||
			len(elem.Body) != len(newOne.Body) {
			continue
		}

		for i, newOneToken := range newOne.Body {
			if newOneToken != elem.Body[i] {
				continue CollectionLoop
			}
		}

		// all checks are passed
		return true
	}

	// there is no equal elements
	return false
}

// assume sets doesn't contains same elements,
// in other words, all elements are unique
func isSameSets(first, second Items) bool {
	if len(first) != len(second) {
		return false
	}

	for _, elem := range first {
		if !containsItem(second, elem) {
			return false
		}
	}

	// all checks are passed
	return true
}

func containsItems(Set ItemsSet, candidate Items) bool {
	for _, presented := range Set {
		if isSameSets(presented, candidate) {
			return true
		}
	}

	return false
}

func constructFirst() {
	for _, t := range GrammarMiniC.Terminals {
		First[t] = make(map[string]struct{})
		First[t][t] = dummy
	}

	for _, nt := range GrammarMiniC.NonTerminals {
		First[nt] = make(map[string]struct{})
	}

	for _, r := range GrammarMiniC.Rules {
		if len(r.Body) == 0 {
			First[r.Name][epsilon] = dummy
		}
	}

	for changed := true; changed; {
		changed = false

		for _, rule := range GrammarMiniC.Rules {
			if len(rule.Body) == 0 {
				continue
			}

			for i, hasEpsilon := 0, true; hasEpsilon; i++ {
				hasEpsilon = false

				ruleToken := rule.Body[i]
				if _, ok := First[ruleToken][epsilon]; ok {
					hasEpsilon = true
				}

				for terminal := range First[ruleToken] {
					if _, ok := First[rule.Name][terminal]; !ok {
						changed = true
						First[rule.Name][terminal] = dummy
					}
				}

				if i+1 == len(rule.Body) && hasEpsilon {
					First[rule.Name][epsilon] = dummy
					break
				}
			}
		}
	}
}

func closure(I Items) Items {
	for changed := true; changed; {
		changed = false

		for _, item := range I {
			if len(item.Body) == item.DotPos+1 || isTerminal(item.Body[item.DotPos+1]) {
				continue
			}

			firstBa := append([]string{}, item.Body[item.DotPos+2:]...)
			firstBa = append(firstBa, item.Symbol)

			for _, rule2 := range GrammarMiniC.Rules {
				if rule2.Name != item.Body[item.DotPos+1] {
					continue
				}

				for i, hasEpsilon := 0, true; hasEpsilon; i++ {
					hasEpsilon = false

					for b := range First[firstBa[i]] {
						if b == epsilon {
							hasEpsilon = true
							continue
						}

						newItem := Item{
							Rule: Rule{
								Name: rule2.Name,
								Body: append([]string{dot}, rule2.Body...),
							},
							Symbol: b,
							DotPos: 0,
						}

						if !containsItem(I, newItem) {
							I = append(I, newItem)
							changed = true
						}
					}
				}
			}
		}
	}

	return I
}

func gotoItems(I Items, X string) Items {
	var J Items
	for _, item := range I {
		if item.DotPos+1 < len(item.Body) && X == item.Body[item.DotPos+1] {
			alpha := append([]string{}, item.Body[:item.DotPos]...)
			beta := append([]string{}, item.Body[item.DotPos+2:]...)

			newBody := append([]string{}, alpha...)
			newBody = append(newBody, X, dot)
			newBody = append(newBody, beta...)

			J = append(
				J,
				Item{
					Rule: Rule{
						Name: item.Name,
						Body: newBody,
					},
					Symbol: item.Symbol,
					DotPos: item.DotPos + 1,
				},
			)
		}
	}
	return closure(J)
}

func ItemsBuild(startItem Items) ItemsSet {
	constructFirst()

	var C ItemsSet
	C = append(C, closure(startItem))

	for changed := true; changed; {
		changed = false
		for _, I := range C {
			for _, X := range append(GrammarMiniC.NonTerminals, GrammarMiniC.Terminals...) {
				newI := gotoItems(I, X)
				if len(newI) != 0 && !containsItems(C, newI) {
					C = append(C, newI)
					changed = true
				}
			}
		}
	}
	return C
}

func findItems(itemsSet ItemsSet, items Items) int {
	for i, collection := range itemsSet {
		if isSameSets(collection, items) {
			return i
		}
	}
	return -1
}

func buildCanonicaLR1Table(startItems Items) CanonicalTableLR1 {
	table := CanonicalTableLR1{
		Terminals:    GrammarMiniC.Terminals,
		NonTerminals: GrammarMiniC.NonTerminals,
		Action:       map[int]map[string]Action{},
		Goto:         map[int]map[string]int{},
	}

	canonicalItems := ItemsBuild(startItems)

	jsonItems, err := json.Marshal(canonicalItems)
	if err != nil {
		panic(err)
	}

	_ = os.WriteFile("canonicalItems.json", jsonItems, 0644)

	for i := 0; i < len(canonicalItems); i++ {
		table.Action[i] = make(map[string]Action)
		for _, t := range GrammarMiniC.Terminals {
			table.Action[i][t] = errAction
		}

		table.Goto[i] = make(map[string]int)
		for _, nt := range GrammarMiniC.NonTerminals {
			table.Goto[i][nt] = -1
		}
	}

	for i, curr := range canonicalItems {
		for _, punct := range curr {

			if punct.DotPos+1 < len(punct.Body) {
				token := punct.Body[punct.DotPos+1]

				if isTerminal(token) {
					action := table.Action[i][token]
					next := gotoItems(curr, token)
					state := findItems(canonicalItems, next)

					if state == -1 {
						panic("cannot find next state in canonical")
					}

					if action.ActionType != errAction.ActionType &&
						action.NextState != state {
						fmt.Println(i, "Conflict!", action, "shift", state, punct)
					}

					table.Action[i][token] = Action{
						ActionType: "shift",
						NextState:  state,
						Rule:       nullRule,
					}
				}
			} else if punct.DotPos+1 == len(punct.Body) {
				if punct.Name == "S'" {
					table.Action[i]["eof"] = Action{
						ActionType: "accept",
						NextState:  -1,
						Rule:       nullRule,
					}
				} else {

					if act := table.Action[i][punct.Symbol].ActionType; act != "error" {
						fmt.Println(i, "Conflict!", act, "reduce", punct)
					}

					table.Action[i][punct.Symbol] = Action{
						ActionType: "reduce",
						NextState:  -1,
						Rule: Rule{
							Name: punct.Name,
							Body: append([]string{}, punct.Body[:punct.DotPos]...),
						},
					}
				}
			}
		}

		for _, nt := range GrammarMiniC.NonTerminals {
			next := gotoItems(curr, nt)
			state := findItems(canonicalItems, next)
			if state == -1 {
				continue
			}

			if t, ok := table.Goto[i][nt]; ok && t != -1 {
				panic("NOT LR(1)")
			}

			table.Goto[i][nt] = state
		}
	}
	return table
}

func main() {
	grammarFile, err := os.ReadFile("grammarIn.json")
	if err != nil {
		panic(err)
	}

	if err := json.Unmarshal(grammarFile, &GrammarMiniC); err != nil {
		log.Fatal(err)
	}

	constructFirst()

	for key, value := range First {
		fmt.Println(key, value)
	}

	startItems := Items{
		Item{
			Rule: Rule{
				Name: "S'",
				Body: []string{dot, "E"},
			},
			Symbol: "eof",
			DotPos: 0,
		},
	}

	closure(startItems)
	canonicalTable := buildCanonicaLR1Table(startItems)

	jsonCanonicalTable, err := json.Marshal(canonicalTable)
	if err != nil {
		panic(err)
	}

	_ = os.WriteFile("canonicalTable.json", jsonCanonicalTable, 0644)
}
