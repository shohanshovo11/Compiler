#include<bits/stdc++.h>
using namespace std;
#define MOD 15
class SymbolInfo
{
    string symbol,symbolType;
public:
    SymbolInfo(string symbol,string symbolType)
    {
        this->symbol = symbol;
        this->symbolType = symbolType;
    }
    string getSymbol()
    {
        return symbol;
    }
    string getSymbolType()
    {
        return symbolType;
    }
    void setSymbol(string symbol)
    {
        this->symbol = symbol;
    }
    void setSymbolType(string symbolType)
    {
        this->symbolType = symbolType;
    }
};
class SymbolTable
{
    vector<SymbolInfo>symTable[MOD];
public:
    void insert(string symbol,string symbolType);
    int hashf(string symbol);
    int lookup(string symbol);
    void delInfo(string symbol);
    void print();
};
int SymbolTable::hashf(string symbol)
{
    int sum = 0;
    if(symbol.length()>=1)sum+=symbol[0];
    if(symbol.length()>=2)sum+=symbol[1];
    if(symbol.length()>=3)sum+=symbol[2];
    return ((sum*94)%MOD);
}
void SymbolTable::insert(string symbol,string symbolType)
{
    SymbolInfo si = SymbolInfo(symbol,symbolType);
    int idx = hashf(symbol);
    int sz = symTable[idx].size();
    for(auto x:symTable[idx])
    {
        if(x.getSymbol()==symbol)
        {
            cout<<"Symbol is already present"<<endl;
            return;
        }
    }
    symTable[idx].push_back(si);
    cout<<"Inserted at position "<<idx<<","<<sz<<endl;
}
int SymbolTable::lookup(string symbol)
{
    int idx = hashf(symbol);
    int index = 0;
    for(auto obj:symTable[idx])
    {
        if(obj.getSymbol()==symbol)
        {
            cout<<"Found at "<<idx<<","<<index<<endl;
            return idx;
        }
        index++;
    }
    cout<<"Symbol not found"<<endl;
    return -1;
}
void SymbolTable::delInfo(string symbol)
{
    int idx = hashf(symbol);
    int id = 0;
    for(auto it = symTable[idx].begin();it!=symTable[idx].end();it++)
    {
        if(it->getSymbol()==symbol)
        {
            cout<<"Deleted from "<<idx<<", "<<id<<endl;
            symTable[idx].erase(it);
            return;
        }
        id++;
    }
    cout<<"Symbol not found."<<endl;
    return;
}
void SymbolTable::print()
{
    int sz = MOD;
    for(int i=0;i<sz;i++)
    {
        cout<<i<<" -> ";
        for(int j=0;j<symTable[i].size();j++)
        {
            cout<<"<"<<symTable[i][j].getSymbol()<<", "<<symTable[i][j].getSymbolType()<<">"<<" ";
        }
        cout<<endl;
    }
}


int oper_checker(string s)
{
    unordered_map<string,bool>oper[4];
    // 0 - arithmetic,1 - logical,2 - bitwise,3-assignment
    ifstream op("operator.txt");
    string temp="";int k = 0;
    while (getline(op,temp))
    {
        stringstream ss(temp);
        while(ss>>temp)
        {
            oper[k][temp]=true;
        }
        k++;
    }
    for(int i=0;i<4;i++)
    {
        if(oper[i][s])
        {
            return i;
        }
    }
    return -1;
}
int main(){
    string inpTyp,inpSymbol,inpSymType;
    SymbolTable st;

///    input from terminal
///    if u want to give input as a file please comment these lines.
//    while(cin>>inpTyp)
//    {
//        if(inpTyp=="I")
//        {
//            cin>>inpSymbol>>inpSymType;
//            st.insert(inpSymbol,inpSymType);
//        }
//        else if(inpTyp=="P")
//        {
//            st.print();
//        }
//        else if(inpTyp=="L")
//        {
//            cin>>inpSymbol;
//            st.lookup(inpSymbol);
//        }
//        else if(inpTyp=="D")
//        {
//            cin>>inpSymbol;
//            st.delInfo(inpSymbol);
//        }
//    }
    ///input from file & output to terminal
//    ifstream file;
//    file.open("input.txt");
//    int ins = 1;
//    if (file.is_open())
//    {
//        while (file >> inpTyp)
//        {
//            cout<<"Instruction - "<<ins<<endl;
//            if (inpTyp == "I")
//            {
//                file >> inpSymbol >> inpSymType;
//                st.insert(inpSymbol, inpSymType);
//            }
//            else if (inpTyp == "P")
//            {
//                st.print();
//            }
//            else if (inpTyp == "L")
//            {
//                file >> inpSymbol;
//                st.lookup(inpSymbol);
//            }
//            else if (inpTyp == "D")
//            {
//                file >> inpSymbol;
//                st.delInfo(inpSymbol);
//            }
//            ins++;
//        }
//    }
//    else
//    {
//        cout<<"file is unable to open."<<endl;
//    }
//    file.close();

    ///Lexical Analyzer - (week-2)
    ///Pre-Processing
    unordered_map<string,bool>keyTable;
    ifstream keywordFile("keyword.txt");
    string temp;
    while(getline(keywordFile,temp))
    {
        keyTable[temp]=true;
    }
//    unordered_map<string,bool>oper[4];
//    // 0 - arithmetic,1 - logical,2 - bitwise,3-assignment
//    ifstream op("operator.txt");
//    temp="";int k = 0;
//    while (getline(op,temp))
//    {
//        stringstream ss(temp);
//        while(ss>>temp)
//        {
//            oper[k][temp]=true;
//        }
//        k++;
//    }
    ///all keyword,operators are loaded.
    ifstream in("sample_input2.txt");
    ofstream ke("out_keyword.txt");
    ofstream fu("out_function.txt");
    ofstream id("out_id.txt");
    ofstream li("out_literal.txt");
    ofstream nu("out_num.txt");
    ofstream opr("out_oper.txt");
    int k=0;
    int line = 1;
    string tx="" ;
    while(getline(in,temp))
    {
        tx="";
        int sz = temp.size();
        string tm = "";
        int i = 0;
        ///Keyword+Function+identifier+number(without exponential) checking
        int func = 0;
        int lit = 0;
        while(i<sz)
        {
            int j;
            for(j=i; j<sz; j++)
            {
                if(temp[j]=='"')lit=(!lit);
                if(lit==1)continue;
                if(temp[j]>='a' && temp[j]<='z' || temp[j]>='A' && temp[j]<='Z'||temp[j]=='_'||(temp[j]>='0'&&temp[j]<='9'))
                {
                    tm+=temp[j];
                }
                else if(tm=="else")
                {
                    if(temp[j]==' ' && temp[j+1]=='i' && temp[j+2]=='f')
                    {
                        tm+=" if";
                        j+=2;
                    }
                    else if(temp[j]==' ')
                    {
                        break;
//                        tm+=temp[j];
//                        j++;

                    }
                    continue;
                }
                else
                {
                    if(temp[j]=='(')
                    {
                        func = 1;
                        cout<<"Lex Error - ( "<<line<<endl;
                    }
                    else if(temp[j]=='.')
                    {
                        cout<<"Lex Error - . "<<line<<endl;
                        tm+=temp[j];
                        continue;
                    }
                    else
                    {
                        tx += temp[j];
                        if(tx==" ")
                        {
                            j++;
                            break;
                        }
                        else if(tx=="+" || tx=="-" ||tx=="*" || tx=="%" ||tx=="&" || tx=="|" || tx=="=")
                        {
                            j++;
                            break;
                        }
                        else
                        {
                            cout<<"Lex Error - "<<tx<<" "<<line<<endl;
                        }

                    }
                    j++;
                    break;
                }
                tx="";
            }
            if(keyTable[tm])
            {
                ke<<tm<<" "<<line<<endl;
                if(func)func=0;
            }
            else if(func && tm!="")
            {
                fu<<tm<<" "<<line<<endl;
                func=0;
            }
            else
            {
                if(tm!="")
                {
                    if(tm[0]>='0' && tm[0]<='9'){
                        nu<<tm<<" "<<line<<endl;
                    }
                    else{
                        id<<tm<<" "<<line<<endl;
                    }
                }
            }
            if(func)func=0;
            i=j;
            tm="";
            tx="";
        }
        line++;
    }
    in.close();
    ///literal checking
    in.open("sample_input2.txt");
    line = 1;
    while(getline(in,temp))
    {
        int sz = temp.size();
        int i = 0;
        string s="";
        int st = 0;
        while(i<sz)
        {
            if(temp[i]=='"')
            {
                st=(!st);
            }
            if(st)
            {
                s+=temp[i];
            }
            if(!st && temp[i]=='"')
            {
                s+='"';
            }
            if(s!="" && st==0)
            {
                li<<s<<" "<<line<<endl;
                st=(!st);
            }
            i++;
        }
        line++;
    }
    in.close();
///operator checking
    in.open("sample_input2.txt");
    line = 1;
    unordered_map<char,bool>op;
    op['+']=true;
    op['-']=true;
    op['*']=true;
    op['&']=true;
    op['|']=true;
    op['<']=true;
    op['>']=true;
    op['=']=true;
    op['/']=true;
    op['%']=true;
    while(getline(in,temp))
    {
        int sz = temp.size();
        int i = 0;
        while(i<sz)
        {
            string s1="";
            string s2="";
            string s3="";
            if(op[temp[i]])
            {
                s1=temp[i];///1st part
                s2=temp[i];///combined
                s2+=temp[i+1];///combined
                s3=temp[i+1];///2nd part
                i+=2;
            }
            else
            {
                i++;
            }
            int a = oper_checker(s1);
            int b = oper_checker(s2);
            int c = oper_checker(s3);
            if(b!=-1)
            {
                if(b==0)
                {
                    opr<<s2<<" "<<"Arithmetic_Operator "<<line<<endl;
                }
                else if(b==1)
                {
                    opr<<s2<<" "<<"Logical_Operator "<<line<<endl;
                }
                else if(b==2)
                {
                    opr<<s2<<" "<<"Bitwise_Operator "<<line<<endl;
                }
                else if(b==3)
                {
                    opr<<s2<<" "<<"Assignment_Operator "<<line<<endl;
                }
            }
            else
            {
                if(a!=-1)
                {
                    if(a==0)
                    {
                        opr<<s1<<" "<<"Arithmetic_Operator "<<line<<endl;
                    }
                    else if(a==1)
                    {
                        opr<<s1<<" "<<"Logical_Operator "<<line<<endl;
                    }
                    else if(a==2)
                    {
                        opr<<s1<<" "<<"Bitwise_Operator "<<line<<endl;
                    }
                    else if(a==3)
                    {
                        opr<<s1<<" "<<"Assignment_Operator "<<line<<endl;
                    }
                }
                if(c!=-1)
                {
                    if(c==0)
                    {
                        opr<<s3<<" "<<"Arithmetic_Operator "<<line<<endl;
                    }
                    else if(c==1)
                    {
                        opr<<s3<<" "<<"Logical_Operator "<<line<<endl;
                    }
                    else if(c==2)
                    {
                        opr<<s3<<" "<<"Bitwise_Operator "<<line<<endl;
                    }
                    else if(c==3)
                    {
                        opr<<s3<<" "<<"Assignment_Operator "<<line<<endl;
                    }
                }
            }
        }
        line++;
    }





    return 0;
}
