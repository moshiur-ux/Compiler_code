#include<bits/stdc++.h>
using namespace std;
bool checkOp(int a, int b, string op){
    if(op == "==")  return a == b;
    else if(op == ">")   return a > b;
    else if(op == "<")   return a < b;
    else if(op == ">=")  return a >= b;
    else if(op == "<=")  return a <= b;
    else if(op == "&&")  return a && b;
    else if(op == "||")  return a || b;
    else return false;
}
bool condition_checker(string tokens){
    smatch condition;
    if(regex_match(tokens,condition,regex("\\s*(.*)\\s*(==|>=|<=|>|<|&&|\\|\\|)\\s*(.*)\\s*"))){
        string first,op,second;
        first = condition.str(1);
        op = condition.str(2);
        second = condition.str(3);
        int a,b;
        if(isdigit(first[0])){
            a = stoi(first);
        }else{
            // a = stoi(variable[first].second);
        }
        if(isdigit(second[0])){
            b = stoi(second);
        }else{
            // b = stoi(variable[second].second);
        }
        return checkOp(a,b,op);

    }
    return false;
}
bool printf_function(string line){
    vector<string> v;
    stringstream ss(line);
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        v.push_back(substr);
    }
    const regex r("(%d|%c|%lf|%f|%s)");
    const std::string in = v[0].substr(1,v[0].length()-2);
    std::string out = in;
    int i = 1;
    // while (std::regex_search(out, r)) {
    //     out = std::regex_replace(out, r, variable[v[i]].second,regex_constants::format_first_only);
    //     i++;
    // }
    cout<<out<<endl;
    return true;
}
int main(){
    vector<string> source_code;
    vector<int> line_number;
    ifstream file("source.c");
    string line;
    int line_count = 0;
    while (getline(file, line)){
        line_count++;
        line = regex_replace(line,regex("^\\s+|\\s+$"),"");
        if(line != ""){
            source_code.push_back(line);
            line_number.push_back(line_count);
        } 
    }
    file.close();
    int main_start = 0;
    int main_end = -1;
    bool flag = false;
    bool err = false;
    bool is_found = false;
    stack<string> braices;
    int last_braices = 0;
    for(int it = 0;it < source_code.size();it++){
        if(regex_match(source_code[it],regex("(?:int|void)\\s+main\\s*\\(\\)\\s*\\{?"))){
                flag = true;
                main_start = it;
        }
        if(flag){
            if(regex_match(source_code[it],regex(".*\\{.*"))){
                braices.push("{");
                is_found = true;
            }
            if(regex_match(source_code[it],regex(".*\\}.*"))){
                if(!braices.empty()){
                    braices.pop();
                }else{
                    cout<<"Imbalance got } at "<<line_number[last_braices]<<endl;
                    err = true;
                }
                if(braices.empty() && is_found){
                    main_end = it;
                    flag = false;   
                }
            }
        }
        else{
            if(regex_match(source_code[it],regex(".*\\{.*"))){
                braices.push("{");
                last_braices = it;
            }
            else if(regex_match(source_code[it],regex(".*\\}.*"))){
                if(braices.empty()){
                    cout<<"Imbalance got } at "<<line_number[last_braices]<<endl;
                    err = true;
                    continue;
                }
                braices.pop();
            }
        }
    }
    if(!braices.empty()){
        cout<<"Imbalance { at"<<line_number[last_braices]<<endl;
        err = true;
    }

    bool if_founded = false;
    bool if_true = false;
    stack<string> condition_braices;
    for(int it = main_start;it <= main_end;it++){
        smatch cond;
        //Checking condition
        if(regex_match(source_code[it],cond,regex("if\\s*\\(\\s*(.*)\\s*\\)\\{?"))){
            if_founded = true;
            bool result = condition_checker(cond.str(1));
            if(result){
                if_true = true;
            }
            else{
                while(it<=main_end){
                    if(regex_match(source_code[it],regex(".*\\{.*"))){
                        condition_braices.push("{");
                    }
                    if(regex_match(source_code[it],regex(".*\\}.*"))){
                        if(!condition_braices.empty()){
                            condition_braices.pop();
                        }
                    }
                    if(condition_braices.empty()){
                        break;
                    }
                    it++;
                }
            }
        }
        if(regex_match(source_code[it],cond,regex(".*else\\s*\\{?"))){
            if(if_founded){
                if(if_true){
                    while(it<=main_end){
                        if(regex_match(source_code[it],regex(".*\\{.*"))){
                            condition_braices.push("{");
                        }
                        if(regex_match(source_code[it],regex(".*\\}.*"))){
                            if(!condition_braices.empty()){
                                condition_braices.pop();
                            }
                        }
                        if(condition_braices.empty()){
                            break;
                        }
                        it++;
                    }
                }
            }else{
                cout<<"Else statement is not allow without if statement! on line "<<line_number[it]<<endl;
            }
        }
        smatch func;
        if(regex_match(source_code[it],func,regex("printf\\((.*)\\)\\s*;"))){
            printf_function(func.str(1));
        }
    }
    
    return 0;
}

