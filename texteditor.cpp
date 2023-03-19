#include <bits/stdc++.h>
using namespace std;
class Editor {
    private:
        vector<string> texteditor;
        int n=0;
        vector<vector<string>> undo;
        vector <vector<string>> redo;
        int leun=0;
        int lere=0;
    public:
        void delappend(int un=1,int re=0){
          if(un==1){
            undo.push_back({"2",texteditor.back()});  
            leun+=1;
            }
          if(re==0){
            lere=0;
            redo.clear();
          }
          if(re==1){
            lere+=1;
            redo.push_back({"2",texteditor.back()});
          }
          texteditor.pop_back();
          n-=1;
        }
        void insert(int pos,string val,int un=1,int re=0){
          if(pos<=n){
            if(un==1){
              leun+=1;
            undo.push_back({"4",to_string(pos)});
            }
          if(re==0){
            lere=0;
            redo.clear();
          }
          if(re==1){
            lere+=1;
            redo.push_back({"4",to_string(pos)});
          }
            texteditor.insert(texteditor.begin() + pos, val);
            n+=1;
            // cout<<(n)<<endl;
          }
          else{
            cout<<("Invalid Position")<<endl;
          }
        }
        void update(int pos,string val,int un=1,int re=0){
          if(pos<n){
            if(un==1){
              leun+=1;
            undo.push_back({"1",to_string(pos),texteditor[pos]});
            }
          if(re==0){
            lere=0;
            redo.clear();
          }
          if(re==1){
            lere+=1;
            redo.push_back({"1",to_string(pos),texteditor[pos]});
          }
            texteditor[pos]=val;
          }
          else{
            cout<<("Invalid Position")<<endl;
          }
        }
        void append(string val,int un=1,int re=0){
          if(un==1){
            leun+=1;
            undo.push_back({"6"});
            }
          if(re==0){
            lere=0;
            redo.clear();
          }
          if(re==1){
            lere+=1;
            redo.push_back({"6"});
          }
          texteditor.push_back(val);
          n+=1;
          // cout<<(n)<<endl;
        }
        void search(int pos,int un=1,int re=0){
          if(pos<n){
            if(un==1){
              leun+=1;
            undo.push_back({"3",to_string(pos)});
            }
          if(re==0){
            lere=0;
            redo.clear();
          }
          if(re==1){
            lere+=1;
            redo.push_back({"3",to_string(pos)});
          }
            cout<<texteditor[pos]<<endl;
          }
          else{
            cout<<"Invalid Position"<<endl;
          }
        }
        void del(int pos,int un=1,int re=0){
          if(pos<n){
            if(un==1){
              leun+=1;
            undo.push_back({"0",to_string(pos),texteditor[pos]});
            }
          if(re==0){
            lere=0;
            redo.clear();
          }
          if(re==1){
            lere+=1;
            redo.push_back({"0",to_string(pos),texteditor[pos]});
          }
            texteditor.erase(texteditor.begin() + pos);
            n-=1;
          }
          else{
            cout<<"Invalid Position"<<endl;
          }
        }
        void display(int un=1,int re=0){
          if(un==1){
            leun+=1;
            undo.push_back({"5"});
            }
          if(re==0){
            lere=0;
            redo.clear();
          }
          if(re==1){
            lere+=1;
            redo.push_back({"5"});
          }
          for (auto val : texteditor) {
            std::cout << val << endl;
          }
        }
        void undoo(){
          vector<string> last;
          int fun,pos;
          string val;
          if(leun>0){
            last = undo.back();
            undo.pop_back();
            leun-=1;
            fun=stoi(last[0]);
            switch(fun){
              case 6:
                delappend(0,1);
                break;
              case 0:
                insert(stoi(last[1]),last[2],0,1);
                break;
              case 1:
                update(stoi(last[1]),last[2],0,1);
                break;
              case 2:
                append(last[1],0,1);
                break;
              case 3:
                search(stoi(last[1]),0,1);
                break;
              case 4:
                del(stoi(last[1]),0,1);
              case 5:
                display(0,1);
                break;
              }
          }
          else{
            cout<<"UNDO STACK IS EMPTY!!!"<<endl;
          }
        }
        void redoo(){
          vector<string> last;
          int fun,pos;
          string val;
          if(lere>0){
            last = redo.back();
            redo.pop_back();
            lere-=1;
            fun=stoi(last[0]);
            switch(fun){
              case 6:
                delappend(1,2);
                break;
              case 0:
                insert(stoi(last[1]),last[2],1,2);
                break;
              case 1:
                update(stoi(last[1]),last[2],1,2);
                break;
              case 2:
                append(last[1],1,2);
                break;
              case 3:
                search(stoi(last[1]),1,2);
                break;
              case 4:
                del(stoi(last[1]),1,2);
              case 5:
                display(1,2);
                break;
              }
          }
          else{
            cout<<"REDO STACK IS EMPTY!!!"<<endl;
          }
        }
        void save(){
          ofstream MyFile("TextEditor.txt");
          for (auto val : texteditor) {
            MyFile<<val<<'\n';
            }
          MyFile.close();
        }

};

int main() {
  Editor person;
  int inp,fl,pos,ill;
  string val;
  ill=5;
  while(true){
    cout<<"Illegal Attempts Left: "<<ill<<endl;
    cout<<"Press 0 to insert"<<endl;
    cout<<"Press 1 to update"<<endl;
    cout<<"Press 2 to append"<<endl;
    cout<<"Press 3 to search"<<endl;
    cout<<"Press 4 to delete"<<endl;
    cout<<"Press 5 to display"<<endl;
    cout<<"Press 6 to undo"<<endl;
    cout<<"Press 7 to redo"<<endl;
    cout<<"Press 8 to exit and save in storage"<<endl;
    cin>> inp;
    fl=0;
    switch(inp){
      case 0:
        cout<<"Position"<<endl;
        cin>>pos;
        cout<<"Value"<<endl;
        cin>>val;
        person.insert(pos,val);
        break;
      case 1 :
        cout<<"Position"<<endl;
        cin>>pos;
        cout<<"Value"<<endl;
        cin>>val;
        person.update(pos,val);
        break;
      case 2 :
        cout<<"Value"<<endl;
        cin>>val;
        person.append(val);
        break;
      case 3 :
        cout<<"Position"<<endl;
        cin>>pos;
        person.search((int) pos);
        break;
      case 4 :
        cout<<"Position"<<endl;
        cin>>pos;
        person.del((int) pos);
        break;
      case 5:
        person.display();
        break;
      case 6:
        person.undoo();
        break;
      case 7:
        person.redoo();
        break;
      case 8:
        person.save();
        fl=1;
        break;
      default :
        ill--;
        break;
    }
    if(fl==1 || ill==0){
      break;
    }
  }
  cout<<"Program Exit, Thank You!!"<<endl;
    return 0;
}