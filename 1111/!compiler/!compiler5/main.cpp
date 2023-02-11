#include <bits/stdc++.h>
using namespace std;
int main() {
    ifstream source_file("sample.txt");
    vector<string> source_code;
    vector<int> line_number;
    vector<string> headers;
    map<string,pair<string,string>> variable;
    bool errors = false;
    if(source_file.is_open()) {
        string line_read;
        bool flag1 = true;
        int line_count=0;
        while(getline(source_file, line_read)) {
            line_count++;
            line_read = regex_replace(line_read,regex("^\\s+|\\s+$"),"");
            line_read = regex_replace(line_read,regex("//.+$"),"");
            if(regex_match(line_read,regex("/\\*.*"))){
                flag1 = false;
            }
            if(regex_match(line_read,regex("\\*/.*"))){
                flag1 = true;
                continue;
            }
            if(flag1){
                if(line_read != ""){
                    source_code.push_back(line_read);
                    line_number.push_back(line_count);
                }
            }
        }
    } else {
        cerr <<"There is no such file exist!\n";
        errors = true;
    }
    bool is_main_found = false;
    bool is_return_found = false;
    if(!errors){
        bool flag2 = false;
        stack<string> braches;
        int main_start_line = 0;
        int main_end_line = 0;
        bool is_braches_found = false;
        int lb = 0;
        for(int it = 0;it < source_code.size();it++){
            smatch head;
            if(regex_match(source_code[it],head,regex("#\\s*include\\s*<([\\w\\s\\.]*)>"))){
                headers.push_back(head.str(1));
            }

            if(regex_match(source_code[it],regex("(?:int|void)\\s+main\\s*\\(\\)\\s*\\{?"))){
                flag2 = true;
                is_main_found = true;
                main_start_line = it;
            }
		smatch var;
            if(regex_match(source_code[it],var,regex("(int|void|float|double|char)\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*\\w+\\s*;"))){
                variable[var.str(2)].first = var.str(1);
                variable[var.str(2)].second = line_number[it];
            }
            if(regex_match(source_code[it],var,regex("(int|void|float|double|char)\\s+([a-zA-Z_][a-zA-Z0-9_]*\\s*(?:\\s*;|(?:\\s*,\\s*(?:[a-zA-Z_][a-zA-Z0-9_]*))*)*);"))){
                string temp;
                stringstream X(var.str(2));
                while(getline(X,temp,',')){
                    temp.erase(std::remove(temp.begin(), temp.end(), ' '), temp.end());
                    variable[temp].first = var.str(1);
                    variable[temp].second = line_number[it];
                }
            }
            
            if(flag2){
                if(regex_match(source_code[it],regex(".*\\{.*"))){
                    braches.push("{");
                    is_braches_found = true;
                }
                if(regex_match(source_code[it],regex(".*\\}.*"))){
                    if(!braches.empty()){
                        braches.pop();
                    }else{
                        cout<<"extra { token on "<<line_number[lb]<<endl;
                        errors = true;
                    }
                    
                    if(braches.empty() && is_braches_found){
                        main_end_line = it;
                        flag2 = false;   
                    }
                }
            }
            else{
                if(regex_match(source_code[it],regex(".*\\{.*"))){
                    braches.push("{");
                    lb = it;
                }
                else if(regex_match(source_code[it],regex(".*\\}.*"))){
                    if(braches.empty()){
                        cout<<"Imbalance { on "<<line_number[lb];
                        errors = true;
                        continue;
                    }
                    braches.pop();
                }
            }
            if(regex_match(source_code[it],regex(".*return\\s+0\\s*;"))){
                is_return_found = true;
            }
        }
        if(!braches.empty()){
            cout<<"Imbalance { on "<<line_number[lb]<<endl;
            errors = true;
        }
    }
    if(!is_return_found){
        cout<<"No return statement found!"<<endl;
        errors = true;
    }
    if(!is_main_found){
        cout<<"No main function found!"<<endl;
        errors = true;
    }
    if(!headers.size()){
        cout<<"No header is defined!"<<endl;
        errors = true;
    }
    if(!errors){
        cout<<"Variables are : "<<endl;
        for(auto var : variable){
            cout<<var.first<<endl;
        }
        cout<<endl;
        cout << "build successfully1!!\n";
    }
    return 0;
}