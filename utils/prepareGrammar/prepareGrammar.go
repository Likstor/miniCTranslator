package main

import (
	"encoding/json"
	"fmt"
	"log"
	"os"
)

type Token struct {
	LexemeType string
	Value      string
}

type Rule struct {
	LeftPart  string
	RightPart []Token
}

type Grammar struct {
	Rules        []Rule
	Terminals    []string
	Nonterminals []string
}

type Item struct {
	LeftPart  string
	RightPart []Token
	Symbol    Token
	dotPos    int
}

type Items []Item

type ItemsSet []Items

type Action struct {
	ActionType string
	Pos        int
	Rule       Rule
}

type CanonicalTableLR1 struct {
	Goto         map[int]map[string]int
	Action       map[int]map[string]Action
	StartPos     int
	Terminals    []string
	Nonterminals []string
}

var (
	First        = map[string]map[string]bool{}
	GrammarMiniC Grammar
)

func isTerminal(chr string) bool {
	for i := 0; i < len(GrammarMiniC.Terminals); i++ {
		if chr == GrammarMiniC.Terminals[i] {
			return true
		}
	}
	return false
}

func containsItem(I Items, item Item) bool {
	for _, obj := range I {
		check := true

		if obj.LeftPart == item.LeftPart &&
			obj.dotPos == item.dotPos &&
			obj.Symbol.LexemeType == item.Symbol.LexemeType {
			if len(obj.RightPart) != len(item.RightPart) {
				continue
			}

			for i, tkn := range item.RightPart {
				if tkn.LexemeType == obj.RightPart[i].LexemeType {
					continue
				}
				check = false
				break
			}
			if check {
				return true
			}
		}
	}
	return false
}

func containsItems(I ItemsSet, candidate Items) bool {
	for _, presented := range I {
		counter := 0

		if len(presented) != len(candidate) {
			continue
		}

		for _, elem := range presented {
			if containsItem(candidate, elem) {
				counter++
			}
		}

		if len(candidate) == counter {
			return true
		}
	}
	return false
}

func constructFirst() {
	for _, terminal := range GrammarMiniC.Terminals {
		First[terminal] = make(map[string]bool)
		First[terminal][terminal] = false
	}

	for _, nonterminal := range GrammarMiniC.Nonterminals {
		First[nonterminal] = make(map[string]bool)
	}

	for _, rule := range GrammarMiniC.Rules {
		if len(rule.RightPart) == 0 {
			First[rule.LeftPart]["epsilon"] = false
		}
	}

	changed := true
	for changed {
		changed = false

		for _, rule := range GrammarMiniC.Rules {
			if len(rule.RightPart) == 0 {
				continue
			}

			h := 0
			for {
				token := rule.RightPart[h]
				hasEpsilon := false

				for key := range First[token.LexemeType] {
					if _, ok := First[token.LexemeType]["epsilon"]; ok {
						hasEpsilon = true
						continue
					}

					if _, ok := First[rule.LeftPart][key]; !ok {
						changed = true
					}

					First[rule.LeftPart][key] = false
				}

				if h+1 == len(rule.RightPart) && hasEpsilon {
					First[rule.LeftPart]["epsilon"] = false
					break
				}

				if !hasEpsilon {
					break
				}
				h++
			}
		}
	}
}

func closure(I Items) Items {
	changed := true
	for changed {
		changed = false

		var J Items
		J = append(J, I...)

		for _, item := range I {
			if len(item.RightPart) == item.dotPos+1 || isTerminal(item.RightPart[item.dotPos+1].LexemeType) {
				continue
			}

			firstBa := append([]Token{}, item.RightPart[item.dotPos+2:]...)
			firstBa = append(firstBa, item.Symbol)
			firstI := 0

			for _, rule2 := range GrammarMiniC.Rules {
				if rule2.LeftPart != item.RightPart[item.dotPos+1].LexemeType {
					continue
				}

			FirstBaRepeat:
				hasEps := false
				for b := range First[firstBa[firstI].LexemeType] {
					var tempItem Item

					if b == "epsilon" {
						hasEps = true
						continue
					}

					if len(rule2.RightPart) == 0 {
						tempItem = Item{
							rule2.LeftPart,
							[]Token{{"dot", ""}},
							Token{b, ""},
							0,
						}
					} else {
						tempItem = Item{
							rule2.LeftPart,
							append([]Token{{"dot", ""}}, rule2.RightPart...),
							Token{b, ""},
							0,
						}
					}
					if containsItem(J, tempItem) {
						continue
					}

					J = append(J, tempItem)
					changed = true
				}
				if hasEps {
					firstI++
					goto FirstBaRepeat
				}
			}
		}
		I = Items{}
		I = append(I, J...)
	}

	return I
}

func gotoItems(I Items, chr string) Items {
	var J Items
	for _, item := range I {
		if item.dotPos+1 < len(item.RightPart) && item.RightPart[item.dotPos+1].LexemeType == chr {
			alpha := append([]Token{}, item.RightPart[:item.dotPos]...)
			beta := append([]Token{}, item.RightPart[item.dotPos+2:]...)
			rightPartTemp := append([]Token{}, alpha...)
			rightPartTemp = append(rightPartTemp, item.RightPart[item.dotPos+1], Token{"dot", ""})
			rightPartTemp = append(rightPartTemp, beta...)
			J = append(J, Item{item.LeftPart, rightPartTemp, item.Symbol, item.dotPos + 1})
		}
	}
	return closure(J)
}

func ItemsBuild(startItem Items) ItemsSet {
	constructFirst()

	changed := true
	var C ItemsSet
	C = append(C, closure(startItem))

	for changed {
		changed = false
		for _, items := range C {
			

			for _, chr := range append(GrammarMiniC.Nonterminals, GrammarMiniC.Terminals...) {
				gotoChr := gotoItems(items, chr)
				if len(gotoChr) != 0 && !containsItems(C, gotoChr) {
					C = append(C, gotoChr)
					changed = true
				}
			}
		}
	}
	return C
}

func findItems(itemsSet ItemsSet, items Items) int {
	for i, itms := range itemsSet {
		counter := 0
		for _, item := range itms {
			if containsItem(items, item) {
				counter++
			}
		}
		if len(itms) == counter {
			return i
		}
	}
	return -1
}

func buildCanonicaLR1Table(startItems Items) CanonicalTableLR1 {
	MiniCLR1CanonicalTable := CanonicalTableLR1{}
	MiniCLR1CanonicalTable.Terminals = GrammarMiniC.Terminals
	MiniCLR1CanonicalTable.Nonterminals = GrammarMiniC.Nonterminals
	MiniCLR1CanonicalTable.Action = make(map[int]map[string]Action)
	MiniCLR1CanonicalTable.Goto = make(map[int]map[string]int)

	canonicalItems := ItemsBuild(startItems)

	jsonItems, err := json.Marshal(canonicalItems)
	if err != nil {
		panic(err)
	}

	_ = os.WriteFile("canonicalItems.json", jsonItems, 0644)

	for i := 0; i < len(canonicalItems); i++ {
		MiniCLR1CanonicalTable.Action[i] = make(map[string]Action)
		for _, term := range GrammarMiniC.Terminals {
			MiniCLR1CanonicalTable.Action[i][term] = Action{"error", -1, Rule{"NULL", []Token{}}}
		}

		MiniCLR1CanonicalTable.Goto[i] = make(map[string]int)
		for _, term := range GrammarMiniC.Nonterminals {
			MiniCLR1CanonicalTable.Goto[i][term] = -1
		}
	}

	for i, items := range canonicalItems {
		for _, rule := range items {

			if len(rule.RightPart) > rule.dotPos+1 {
				nextToken := rule.RightPart[rule.dotPos+1].LexemeType

				if isTerminal(nextToken) {
					act := MiniCLR1CanonicalTable.Action[i][nextToken]
					gotoIi := gotoItems(items, nextToken)
					itemsJ := findItems(canonicalItems, gotoIi)

					if itemsJ == -1 {
						panic("ITEMS J -1")
					}

					if act.ActionType != "error" && act.Pos != itemsJ {
						fmt.Println(i, "Conflict!", act, "shift", itemsJ, rule)
					}
					MiniCLR1CanonicalTable.Action[i][nextToken] = Action{"shift", itemsJ, Rule{"NULL", []Token{}}}
					continue
				}
			} else if rule.dotPos+1 == len(rule.RightPart) {
				if rule.LeftPart == "S'" {
					MiniCLR1CanonicalTable.Action[i]["eof"] = Action{"accept", -1, Rule{}}
					continue
				} else {

					if act := MiniCLR1CanonicalTable.Action[i][rule.Symbol.LexemeType].ActionType; act != "error" {
						fmt.Println(i, "Conflict!", act, "reduce", rule)
					}
					MiniCLR1CanonicalTable.Action[i][rule.Symbol.LexemeType] = Action{"reduce", -1, Rule{rule.LeftPart, append([]Token{}, rule.RightPart[:rule.dotPos]...)}}
					continue
				}
			}
		}

		for _, temp := range GrammarMiniC.Nonterminals {
			gotoA := gotoItems(items, temp)
			itemsJ := findItems(canonicalItems, gotoA)
			if itemsJ == -1 {
				continue
			}

			if t, ok := MiniCLR1CanonicalTable.Goto[i][temp]; ok && t != -1 {
				panic("NOT LR(1)")
			}

			MiniCLR1CanonicalTable.Goto[i][temp] = itemsJ

		}
	}
	return MiniCLR1CanonicalTable
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

	startItems := Items{Item{"S'", []Token{{"dot", ""}, {"E", ""}}, Token{"eof", ""}, 0}}

	closure(startItems)
	canonicalTable := buildCanonicaLR1Table(startItems)

	jsonCanonicalTable, err := json.Marshal(canonicalTable)
	if err != nil {
		panic(err)
	}

	_ = os.WriteFile("canonicalTable.json", jsonCanonicalTable, 0644)
}
