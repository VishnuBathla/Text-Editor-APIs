class Editor:
  texteditor=[]
  n=0
  undo=[]
  redo=[]
  def delappend(self,undo=1,redo=0):
    if(redo==1):++
      # print(self)
      self.redo.append(("append",[self.texteditor[-1]]))
    elif(redo==2):
      pass
    else:
      self.redo=[]
    if(undo==1):
      self.undo.append(("append",[self.texteditor[-1]]))
    del self.texteditor[-1]
    self.n-=1
    return None,0
  def append(self,text,undo=1,redo=0):
    self.texteditor.append(text)
    if(redo==1):
      self.redo.append(("delappend",[]))
    elif(redo==2):
      pass
    else:
      self.redo=[]
    if(undo==1):
      self.undo.append(("delappend",[]))
    self.n+=1
    return None,0
  def insert(self,pos,text,undo=1,redo=0):
    pos=int(pos)
    if(self.n>=pos):
      self.texteditor.insert(pos,text)
      if(redo==1):
        self.redo.append(("delete",[pos,text]))
      elif(redo==2):
        pass
      else:
        self.redo=[]
      if(undo==1):
        self.undo.append(("delete",[pos,text]))
      self.n+=1
    else:
      print(Exception('INVALID POSITION'))
    return None,0
  def update(self,pos,text,undo=1,redo=0):
    pos=int(pos)
    if(self.n>pos):
      if(redo==1):
        self.redo.append(("update",[pos,self.texteditor[pos]]))
      elif(redo==2):
        pass  
      else:
        self.redo=[]
      if(undo==1):
        self.undo.append(("update",[pos,self.texteditor[pos]]))
      self.texteditor[pos]=text
    else:
      print(Exception('INVALID POSITION'))
    return None,0
  def search(self,pos,undo=1,redo=0):
    pos=int(pos)
    if(self.n>pos):
      if(redo==1):
        self.redo.append(("search",[pos]))
      elif(redo==2):
        pass  
      else:
        self.redo=[]
      if(undo==1):
        self.undo.append(("search",[pos]))
      # print(pos,self.texteditor)
      return self.texteditor[pos],1
    else:
      print(Exception('INVALID POSITION'))
    return None,0
  def delete(self,pos,undo=1,redo=0):
    pos=int(pos)
    if(self.n>pos):
      if(redo==1):
        self.redo.append(("insert",[pos,self.texteditor[pos]]))
      elif(redo==2):
        pass  
      else:
        self.redo=[]
      if(undo==1):
        self.undo.append(("insert",[pos,self.texteditor[pos]]))
      del self.texteditor[pos]
      self.n-=1
    else:
      print(Exception('INVALID POSITION'))
    return None,0
  def display(self,undo=1,redo=0):
    if(redo==1):
      self.redo.append(("display",[]))
    elif(redo==2):
      pass  
    else:
      self.redo=[]
    if(undo==1):
      self.undo.append(("display",[]))
    return ('\n'.join(self.texteditor),1)
  defin={"delappend":delappend,"append":append,"insert":insert,"update":update,"search":search,"delete":delete,"display":display}
  def redoo(self,u=1,r=0):
    print(self.redo)
    if(self.redo):
      a=self.redo.pop(-1)
      if(a[1]==[]):
        return self.defin[a[0]](self,undo=1,redo=2)
      else:
        return self.defin[a[0]](self,*a[1],undo=1,redo=2)
    else:
      print("Redo Stack is Empty")
      return None,0
  def undoo(self,u=1,r=0):
    print(self.undo)
    if(self.undo):
      a=self.undo.pop(-1)
      if(a[1]==[]):
        return self.defin[a[0]](self,undo=0,redo=1)
      else:
        return self.defin[a[0]](self,*a[1],undo=0,redo=1)
    else:
      print("Undo Stack is Empty")
      return None,0
  helper={1:["Insert Data",insert,{"pos":"Position","text":"Text"}],2:["Update Data",update,{"pos":"Position","text":"Text"}],3:["Append",append,{"text":"Text"},0],4:["Search",search,{"pos":"Position"}],5:["Delete",delete,{"pos":"Position"}],6:["Display",display,{},1],7:["Undo",undoo,{},1],8:["Redo",redoo,{},1]}
n=0
while(True):
  print("Press 1 to start")
  n=input()
  if(n.strip()!="1"):
    print('Invalid Input')
  else:
    break
a=Editor()
fl=5
while(True):
  print(f"Invalid Attempts Left {fl}")
  for i in a.helper:
    print(f"Press {i} to {a.helper[i][0]}")
  print("Press 9 to Exit")
  b=int(input())
  if(b==9):
    break
  if(b not in a.helper):
    fl-=1
    print("Invalid Command")
  else:
    inpu=[]
    for i in a.helper[b][2]:
      inpu.append(input(a.helper[b][2][i]+'\n'))
    # if(b==8):
    #   inpu+=[1,0]
    # else:
    #   inpu+=[0,1]
    if(inpu==[]):
      o,p=a.helper[b][1](a)
    else:
      o,p=a.helper[b][1](a,*inpu)
    if(p==1):
      print(o)
    else:
      print("Operation Done")
  if(fl==0):
    print("Invalid Limit Reached")
    print("Exiting Program...")
    break
print("Program Exit, Thank You!!")
