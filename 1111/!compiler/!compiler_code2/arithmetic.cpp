#include<bits/stdc++.h>
using namespace std;
map<string,pair<string,string>> variable;
int precedence(char op){
    if(op == '+'||op == '-')
    return 1;
    if(op == '*'||op == '/')
    return 2;
    return 0;
}
int applyOp(int a, int b, char op){
    switch(op){
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0;
    }
}
int evaluate(string tokens){
    int i;
    stack <int> values;
    stack <char> ops;
    for(i = 0; i < tokens.length(); i++){
        if(tokens[i] == ' ')
            continue;
        else if(tokens[i] == '('){
            ops.push(tokens[i]);
        }
        else if(isdigit(tokens[i])){
            int val = 0;
            while(i < tokens.length() &&
                        isdigit(tokens[i]))
            {
                val = (val*10) + (tokens[i]-'0');
                i++;
            }
            values.push(val);
            i--;
        }
        else if(tokens[i] == ')')
        {
            while(!ops.empty() && ops.top() != '(')
            {
                int val2 = values.top();
                values.pop();
                 
                int val1 = values.top();
                values.pop();
                 
                char op = ops.top();
                ops.pop();
                 
                values.push(applyOp(val1, val2, op));
            }
            if(!ops.empty())
               ops.pop();
        }
        else
        {
            while(!ops.empty() && precedence(ops.top())
                                >= precedence(tokens[i])){
                int val2 = values.top();
                values.pop();
                 
                int val1 = values.top();
                values.pop();
                 
                char op = ops.top();
                ops.pop();
                 
                values.push(applyOp(val1, val2, op));
            }
            ops.push(tokens[i]);
        }
    }
    while(!ops.empty()){
        int val2 = values.top();
        values.pop();
                 
        int val1 = values.top();
        values.pop();
                 
        char op = ops.top();
        ops.pop();
                 
        values.push(applyOp(val1, val2, op));
    }
    return values.top();
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
    while (std::regex_search(out, r)) {
        out = std::regex_replace(out, r, variable[v[i]].second,regex_constants::format_first_only);
        i++;
    }
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
    for(int it = 0;it < source_code.size();it++){
        smatch var;
        if(regex_match(source_code[it],var,regex("(int|float|double|char)\\s+([a-zA-Z_][a-zA-Z0-0_]*)\\s*;"))){
            if(!variable.count(var.str(2))){
                variable[var.str(2)].first = var.str(1);
                variable[var.str(2)].second = "Nan";
            }
            else{
                err = true;
                cout<<"Variable "<<var.str(2)<<" on line "<<line_number[it]<<" has already been decleared!"<<endl;
            }
        }

        if(regex_match(source_code[it],var,regex("(int|float|double|char)\\s+([a-zA-Z_][a-zA-Z0-0_]*)\\s*=\\s*(.+)\\s*;"))){
            if(!variable.count(var.str(2))){
                variable[var.str(2)].first = var.str(1);
                variable[var.str(2)].second = var.str(3);
            }
            else{
                err = true;
                cout<<"Variable "<<var.str(2)<<" on line "<<line_number[it]<<" has already been decleared!"<<endl;
            }
        }
        if(regex_match(source_code[it],var,regex("([a-zA-Z_][a-zA-Z0-0_]*)\\s*=\\s*(.+)\\s*;"))){
            if(variable.count(var.str(1))){

                smatch exp;
                string str = var.str(2);
                if(regex_match(str,exp,regex("(.*(?:\\+|-|\\*|/).*)"))){
                    variable[var.str(1)].second = to_string(evaluate(exp.str(1)));
                }
                else{
                    variable[var.str(1)].second = var.str(2);
                }
            }
            else{
                err = true;
                cout<<"Variable "<<var.str(1)<<" on line "<<line_number[it]<<" has never been decleared!"<<endl;
            }
        }
        smatch func;
        if(regex_match(source_code[it],func,regex("printf\\((.*)\\)\\s*;"))){
            printf_function(func.str(1));
        }


    }
    
     
    

    return 0;
}