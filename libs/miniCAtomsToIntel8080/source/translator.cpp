#pragma once
#include <miniCAtomsToIntel8080/translator.h>
#include <format>
#include <string>


namespace miniCAtomsToIntel8080
{
    Translator::Translator(miniCSemanticAnalyzer::SymbolTable &symtable, std::unordered_map<std::string, std::vector<miniCSemanticAnalyzer::Atom>> &functionMap) : symtable{symtable}, functionMap{functionMap}
    {
        outputASM.open("./output/i8080.asm");
        contextMap = symtable.GetContextMap();
    }

    void Translator::popN(int n)
    {
        // Записываем POP B n-раз
        for (int i = 0; i < n; i++)
        {
            outputASM << "POP B" << std::endl;
        }
        outputASM << std::endl;
    }

    void Translator::pushN(int n)
    {
        // Записываем PUSH B n-раз
        for (int i = 0; i < n; i++)
        {
            outputASM << "PUSH B" << std::endl;
        }
        outputASM << std::endl;
    }

    void Translator::loadOp(const std::string &value, int shift)
    {
        // MVI A, value если это число 
        if (value.starts_with('\''))
        {
            outputASM << std::format("MVI A, {}", value.substr(1, value.size() - 2)) << std::endl;
            return;
        }

        // Получаем информацию из таблицы символов о переменной по ее коду
        miniCSemanticAnalyzer::SymbolData &sd = symtable.GetSymbolData(value);

        // LDA var_name если переменная в глобальном контексте
        if (sd.Scope == -1)
        {
            outputASM << std::format("LDA {}", sd.Name) << std::endl;
            return;
        }

        // Записываем сдвиг переменной в ее контексте
        int offsetShift = sd.Offset;

        // Проходимся по вектору контекстов
        for (size_t i = contextArray.size() - 1; i > 0; --i)
        {
            // Если попали в контекст функции, то заканчиваем
            if (sd.Scope == contextArray[i])
            {
                break;
            }
            /*
            Иначе записываем сдвиг относительно количества переменных
            в этом контексте
            */
            offsetShift += contextMap[contextArray[i]].Len * 2;
        }

        outputASM << std::format("LXI H, {}; load from {}", offsetShift + shift, sd.Name) << std::endl
                  << "DAD SP" << std::endl
                  << "MOV A, M" << std::endl
                  << std::endl;
    }

    void Translator::saveOp(const std::string &value)
    {
        // Получаем информацию из таблицы символов о переменной по ее коду
        miniCSemanticAnalyzer::SymbolData &sd = symtable.GetSymbolData(value);

        // STA var_name если переменная в глобальном контексте
        if (sd.Scope == -1)
        {
            outputASM << std::format("STA {}", sd.Name) << std::endl;
            return;
        }

        // Записываем сдвиг переменной в ее контексте
        int offsetShift = sd.Offset;

        // Проходимся по вектору контекстов
        for (size_t i = contextArray.size() - 1; i > 0; --i)
        {
            // Если попали в контекст функции, то заканчиваем
            if (sd.Scope == contextArray[i])
            {
                break;
            }
            /*
            Иначе записываем сдвиг относительно количества переменных 
            в этом контексте
            */
            offsetShift += contextMap[contextArray[i]].Len * 2;
        }

        outputASM << std::format("LXI H, {}; save in {}", offsetShift, sd.Name) << std::endl
                  << "DAD SP" << std::endl
                  << "MOV M, A" << std::endl
                  << std::endl;
    }

    void Translator::loader()
    {
        outputASM << "ORG 8000H" << std::endl;

        for (auto code : symtable.GetContextMap()[-1].Vars)
        {
            miniCSemanticAnalyzer::SymbolData &tmpSd = symtable.GetSymbolData(std::to_string(code));
            outputASM << std::format("{}: DB {}", tmpSd.Name, tmpSd.Init) << std::endl;
        }

        outputASM << "ORG 0" << std::endl
                  << std::endl;

        outputASM << "LXI H, 0" << std::endl
                  << "SPHL" << std::endl
                  << "PUSH B" << std::endl
                  << "CALL func_main_0" << std::endl
                  << "END" << std::endl
                  << "@MULT: ..." << std::endl
                  << "@PRINT: ..." << std::endl
                  << std::endl;
    }

    void Translator::OR(miniCSemanticAnalyzer::Atom &atom)
    {
        loadOp(atom.GetSecond());
        outputASM << "MOV B, A" << std::endl;
        loadOp(atom.GetFirst());
        outputASM << "ORA B" << std::endl;
        saveOp(atom.GetThird());
        outputASM << std::endl;
    }

    void Translator::AND(miniCSemanticAnalyzer::Atom &atom)
    {
        loadOp(atom.GetSecond());
        outputASM << "MOV B, A" << std::endl;
        loadOp(atom.GetFirst());
        outputASM << "ANA B" << std::endl;
        saveOp(atom.GetThird());
        outputASM << std::endl;
    }

    void Translator::MOV(miniCSemanticAnalyzer::Atom &atom)
    {
        loadOp(atom.GetFirst());
        saveOp(atom.GetThird());
    }

    void Translator::EQ(miniCSemanticAnalyzer::Atom &atom)
    {
        loadOp(atom.GetSecond());
        outputASM << "MOV B, A" << std::endl;
        loadOp(atom.GetFirst());
        outputASM << "CMP B" << std::endl
                  << std::format("JZ {}", atom.GetThird()) << std::endl
                  << std::endl;
    }

    void Translator::NE(miniCSemanticAnalyzer::Atom &atom)
    {
        loadOp(atom.GetSecond());
        outputASM << "MOV B, A" << std::endl;
        loadOp(atom.GetFirst());
        outputASM << "CMP B" << std::endl
                  << std::format("JNZ {}", atom.GetThird()) << std::endl
                  << std::endl;
    }

    void Translator::GT(miniCSemanticAnalyzer::Atom &atom)
    {
        loadOp(atom.GetSecond());
        outputASM << "MOV B, A" << std::endl;
        loadOp(atom.GetFirst());
        outputASM << "CMP B" << std::endl
                  << std::format("JP {}", atom.GetThird()) << std::endl
                  << std::endl;
    }

    void Translator::LT(miniCSemanticAnalyzer::Atom &atom)
    {
        loadOp(atom.GetSecond());
        outputASM << "MOV B, A" << std::endl;
        loadOp(atom.GetFirst());
        outputASM << "CMP B" << std::endl
                  << std::format("JM {}", atom.GetThird()) << std::endl
                  << std::endl;
    }

    void Translator::LE(miniCSemanticAnalyzer::Atom &atom)
    {
        loadOp(atom.GetSecond());
        outputASM << "MOV B, A" << std::endl;
        loadOp(atom.GetFirst());
        outputASM << "CMP B" << std::endl
                  << std::format("JM {}", atom.GetThird()) << std::endl
                  << std::format("JZ {}", atom.GetThird()) << std::endl
                  << std::endl;
    }

    void Translator::LBL(miniCSemanticAnalyzer::Atom &atom)
    {
        outputASM << std::format("{}:", atom.GetThird()) << std::endl;
    }

    void Translator::ADD(miniCSemanticAnalyzer::Atom &atom)
    {
        loadOp(atom.GetSecond());
        outputASM << "MOV B, A" << std::endl;
        loadOp(atom.GetFirst());
        outputASM << "ADD B" << std::endl;
        saveOp(atom.GetThird());
        outputASM << std::endl;
    }

    void Translator::SUB(miniCSemanticAnalyzer::Atom &atom)
    {
        loadOp(atom.GetSecond());
        outputASM << "MOV B, A" << std::endl;
        loadOp(atom.GetFirst());
        outputASM << "SUB B" << std::endl;
        saveOp(atom.GetThird());
        outputASM << std::endl;
    }

    void Translator::MUL(miniCSemanticAnalyzer::Atom &atom)
    {
        loadOp(atom.GetSecond());
        outputASM << "MOV D, A" << std::endl;
        loadOp(atom.GetFirst());
        outputASM << "NOV C, A" << std::endl;

        outputASM << "CALL @MULT" << std::endl;
        saveOp(atom.GetThird());
        outputASM << std::endl;
    }

    void Translator::NOT(miniCSemanticAnalyzer::Atom &atom)
    {
        loadOp(atom.GetFirst());
        outputASM << "CMA" << std::endl;
        saveOp(atom.GetThird());
        outputASM << std::endl;
    }

    void Translator::CALL(miniCSemanticAnalyzer::Atom &atom)
    {
        miniCSemanticAnalyzer::SymbolData &sd = symtable.GetSymbolData(atom.GetFirst());

        int len = std::stoi(sd.Len);

        pushN(len + 1);

        for (int i = 1; i <= len; i++)
        {
            loadOp(programStack.top(), (len + 1) * 2);
            programStack.pop();

            outputASM << std::format("LXI H, {}", i * 2) << std::endl
                      << "DAD SP" << std::endl
                      << "MOV A, M" << std::endl
                      << std::endl;
        }

        outputASM << std::format("CALL {}", symtable.GetSymbolData(atom.GetFirst()).Name) << std::endl;

        popN(len + 1);

        outputASM << "MOV A, C" << std::endl;

        saveOp(atom.GetThird());
    }

    void Translator::PARAM(miniCSemanticAnalyzer::Atom &atom)
    {
        programStack.push(atom.GetThird());
    }

    void Translator::RET(miniCSemanticAnalyzer::Atom &atom)
    {
        loadOp(atom.GetThird());

        // Счетчик для количества переменных, которое необходимо снять со стека
        int countVars = 0;
        // Цикл по вектору контекстов
        for (size_t i = 0; i < contextArray.size(); i++)
        {
            // Записываем количество переменных в контексте
            countVars += contextMap[contextArray[i]].Len;
        }

        /* 
        Как сдвиг будет записано (countVars - 1) * 2. Вычитая единицу мы
        получим сдвиг к возвращаемому значению.
        */
        outputASM << std::format("LXI H, {}", (countVars - 1) * 2) << std::endl
                  << "DAD SP" << std::endl
                  << "MOV M, A" << std::endl;

        /*
        Снимаем со стека все переменные, кроме адреса возврата, возвращаемого значения
        и параметров функции.
        */
        popN(countVars - std::stoi(funcSd.Len) - 2);

        outputASM << "RET" << std::endl
                  << std::endl;
    }

    void Translator::JMP(miniCSemanticAnalyzer::Atom &atom)
    {
        outputASM << std::format("JMP {}", atom.GetThird()) << std::endl;
    }

    void Translator::IN(miniCSemanticAnalyzer::Atom &atom)
    {
        outputASM << "IN 0" << std::endl;
        saveOp(atom.GetThird());
        outputASM << std::endl;
    }

    void Translator::OUT(miniCSemanticAnalyzer::Atom &atom)
    {
        loadOp(atom.GetThird());
        outputASM << "OUT 1" << std::endl;
    }

    void Translator::ENTERCTX(int scope)
    {
        // Добавляем новый контекст в вектор
        contextArray.push_back(scope);
        // Выделяем необходимое место для переменных на стеке
        pushN(contextMap[contextArray.back()].Len);
    }

    void Translator::EXITCTX()
    {
        // Снимаем необходимо количество переменных со стека
        popN(contextMap[contextArray.back()].Len);
        // Удаляем последний контекст из вектора
        contextArray.pop_back();
    }

    void Translator::run()
    {
        // Инициализируем программу (глобальные переменные и вызов main)
        loader();

        // Цикл по функция и привязанным к ним атомам
        for (auto &&[funcCode, atoms] : functionMap)
        {
            // Получаем информацию о функции из таблицы символов
            funcSd = symtable.GetSymbolData(funcCode);
            // Записываем метку функции
            outputASM << std::format("{}:", funcSd.Name) << std::endl;

            // Получаем контекст функции из первого атома, т.к. этим атомом является ENTERCTX
            int funcScope = std::stoi(atoms[0].GetThird());
            // Добавляем контекст в вектор контекстов
            contextArray.push_back(funcScope);
            // Выделяем необходимое количество места на стеке для переменных контекста тела функции
            pushN(contextMap[contextArray.back()].Len - 2 - std::stoi(funcSd.Len));

            /* 
            Проходим по всем атомам начиная со второго атома и до предпоследнего.
            Идем до предпоследнего, т.к. это всегда будет RET и он снимет необходимое
            количество переменных со стека и выйдет из функции, следовательно нам 
            нет необходимости обрабатывать последний EXITCTX, 
            ибо появившиеся POP B никогда не будут выполняться.
            */
            for (size_t i = 1; i < atoms.size() - 1; i++)
            {
                miniCSemanticAnalyzer::Atom atom = atoms[i];

                switch (atom.GetType())
                {
                case miniCSemanticAnalyzer::AtomType::OR:
                    OR(atom);
                    break;
                case miniCSemanticAnalyzer::AtomType::AND:
                    AND(atom);
                    break;
                case miniCSemanticAnalyzer::AtomType::MOV:
                    MOV(atom);
                    break;
                case miniCSemanticAnalyzer::AtomType::EQ:
                    EQ(atom);
                    break;
                case miniCSemanticAnalyzer::AtomType::NE:
                    NE(atom);
                    break;
                case miniCSemanticAnalyzer::AtomType::GT:
                    GT(atom);
                    break;
                case miniCSemanticAnalyzer::AtomType::LT:
                    LT(atom);
                    break;
                case miniCSemanticAnalyzer::AtomType::LE:
                    LE(atom);
                    break;
                case miniCSemanticAnalyzer::AtomType::LBL:
                    LBL(atom);
                    break;
                case miniCSemanticAnalyzer::AtomType::ADD:
                    ADD(atom);
                    break;
                case miniCSemanticAnalyzer::AtomType::SUB:
                    SUB(atom);
                    break;
                case miniCSemanticAnalyzer::AtomType::MUL:
                    MUL(atom);
                    break;
                case miniCSemanticAnalyzer::AtomType::NOT:
                    NOT(atom);
                    break;
                case miniCSemanticAnalyzer::AtomType::CALL:
                    CALL(atom);
                    break;
                case miniCSemanticAnalyzer::AtomType::PARAM:
                    PARAM(atom);
                    break;
                case miniCSemanticAnalyzer::AtomType::RET:
                    RET(atom);
                    break;
                case miniCSemanticAnalyzer::AtomType::JMP:
                    JMP(atom);
                    break;
                case miniCSemanticAnalyzer::AtomType::IN:
                    IN(atom);
                    break;
                case miniCSemanticAnalyzer::AtomType::OUT:
                    OUT(atom);
                    break;
                case miniCSemanticAnalyzer::AtomType::ENTERCTX:
                    ENTERCTX(std::stoi(atom.GetThird()));
                    break;
                case miniCSemanticAnalyzer::AtomType::EXITCTX:
                    EXITCTX();
                    break;
                }
            }

            // Очищаем вектор контекстов
            contextArray.clear();
            outputASM << std::endl;
        }
    }

    void Translator::Translate()
    {
        run();
    }
}