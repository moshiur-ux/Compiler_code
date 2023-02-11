#include<bits/stdc++.h>
using namespace std;
map<string,pair<string,string>> variable;
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
            a = stoi(variable[first].second);
        }
        if(isdigit(second[0])){
            b = stoi(second);
        }else{
            b = stoi(variable[second].second);
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
    bool loop_founded = false;
    int loop_start = 0;
    int loop_end = 0;
    stack<string> condition_braices,loop_braices;
    string loop_variable,loop_inc,loop_condition;
    for(int it = main_start;it <= main_end;it++){
        smatch loop;
        if(regex_match(source_code[it],loop,regex("for\\s*\\(\\s*(.*)\\s*;\\s*(.*)\\s*;\\s*(.*)\\s*\\)\\s*\\{?\\s*"))){
            loop_variable = loop.str(1);
            loop_condition = loop.str(2);
            loop_inc = loop.str(3);
            smatch var;
            if(regex_match(loop_variable,var,regex("(int|float|double|char)\\s+([a-zA-Z_][a-zA-Z0-0_]*)\\s*=\\s*(.+)\\s*"))){
                if(!variable.count(var.str(2))){
                    variable[var.str(2)].first = var.str(1);
                    variable[var.str(2)].second = var.str(3);
                    loop_variable = var.str(2);
                }
                else{
                    err = true;
                    cout<<"Variable "<<var.str(2)<<" on line "<<line_number[it]<<" has already been decleared!"<<endl;
                }
            }

            // For assigning a value to a existing variable in loop
            if(regex_match(loop_variable,var,regex("([a-zA-Z_][a-zA-Z0-0_]*)\\s*=\\s*(.+)\\s*"))){
                if(variable.count(var.str(1))){
                    variable[var.str(1)].second = var.str(2); 
                    loop_variable = var.str(1);
                }
                else{
                    err = true;
                    cout<<"Variable "<<var.str(1)<<" on line "<<line_number[it]<<" has never been decleared!"<<endl;
                }
            }
            loop_founded = true;
            bool b_f = false;
            int temp = it;
            while(temp<=main_end){
                if(regex_match(source_code[temp],regex(".*\\{.*"))){
                    loop_braices.push("{");
                    loop_start = temp;
                    b_f = true;

                }
                if(regex_match(source_code[temp],regex(".*\\}.*"))){
                    if(!loop_braices.empty()){
                        loop_braices.pop();
                    }
                }
                if(b_f && loop_braices.empty()){
                    loop_end = temp-1;

                    break;
                }
                temp++;
            }
            it = loop_start;
        }
        
        smatch func;
        if(regex_match(source_code[it],func,regex("printf\\((.*)\\)\\s*;"))){
            printf_function(func.str(1));
        }
        if(loop_founded){
            if(it == loop_end){
                smatch temp_match;

                if(regex_match(loop_inc,temp_match,regex(".*(\\+\\+|--).*"))){
                    string inc = temp_match.str(1);
                    if(inc=="++"){
                        cout<<variable[loop_variable].second<<" is the\n";
                        variable[loop_variable].second = to_string(stoi(variable[loop_variable].second) +1);
                    }
                    else if(inc=="--"){
                        variable[loop_variable].second = to_string(stoi(variable[loop_variable].second) -1);
                    }
                }
                if(condition_checker(loop_condition)){
                    it = loop_start;
                }else{
                    loop_founded = false;
                }
            }
        }
    }
    
    return 0;
}

