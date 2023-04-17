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
    unordered_map<string,bool>tokenTable;
    ifstream keywordFile("keyword.txt");
    string temp;
    while(keywordFile>>temp)
    {
        tokenTable[temp]=true;
    }
    tokenTable["else if"]=true;
//    for(auto x:tokenTable)
//    {
//        cout<<x.first<<" "<<x.second<<endl;;
//    }
    int quit = 1;
    string s;
    ofstream of("token.txt");
    while(quit==1)
    {
        ///int a,b;
        getline(cin,s);
        if(s.size()==0)quit=0;
        else
        {
            string tok="";
            for(int i=0;i<s.size();i++)
            {
                if(s[i]==' '||s[i]==',')
                {
                    if(tok.size()==0)continue;
                    if(tok=="else")
                    {
                        if(s[i+1]=='i'&&s[i+2]=='f')
                        {
                            tok="else if";
                            i+=2;
                        }
                    }
                    if(tokenTable[tok])
                    {
                        cout<<"keyword-"<<tok<<endl;
                    }
                    else
                    {
                        if(tok[0]>='a' && tok[0]<='z' || tok[0]>='A' && tok[0]<='Z')
                        {
                            cout<<"Identifier-"<<tok<<endl;
                        }
                        else cout<<"Lexical error-"<<tok<<endl;
                    }
                    tok="";
                }
                else
                {
                    tok+=s[i];
                }
//                cout<<tok<<endl;

            }
            if(tokenTable[tok])
            {
                cout<<"keyword-"<<tok;
            }
            else cout<<"Lexical error - "<<tok<<endl;
        }
    }
    return 0;
}
