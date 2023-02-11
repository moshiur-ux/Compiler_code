#include<bits/stdc++.h>
using namespace std;
vector<string> headers;
map<string,vector<string>> header_functions;
void add_headers(){
    header_functions["stdio.h"].push_back("printf");
    header_functions["stdio.h"].push_back("scanf");
    header_functions["stdio.h"].push_back("gets");
    header_functions["stdio.h"].push_back("puts");
    header_functions["stdio.h"].push_back("getline");
    header_functions["conio.h"].push_back("clrscr");
    header_functions["conio.h"].push_back("getch");
    header_functions["conio.h"].push_back("getche");
    header_functions["math.h"].push_back("abs");
    header_functions["math.h"].push_back("floor");
    header_functions["math.h"].push_back("ceil");
    header_functions["math.h"].push_back("random");
    header_functions["math.h"].push_back("round");
    header_functions["math.h"].push_back("truncat");    
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
    add_headers();
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
        smatch head;
        if(regex_match(source_code[it],head,regex("#\\s*include\\s*<([\\w\\s\\.]*)>"))){
            headers.push_back(head.str(1));
        }
    }
    
     
    if(!headers.empty()){
        cout<<"All headers"<<endl;
        for (auto& x: headers) {
            if(header_functions.find(x) != header_functions.end()){
                cout << x<<'\n';
            }else{
                cout<<"no such header name \""<<x<<"\" found !"<<endl;
            }  
        }

    }else{
        cout<<"No header found!"<<endl;
    }

    return 0;
}