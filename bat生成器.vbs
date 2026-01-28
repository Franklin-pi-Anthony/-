'any2bat {s11ss 2008-1-17}
'获取要转换的文件：
If Not WScript.Arguments.Count=1 Then WScript.Echo "将要转换的文件托拽到我身上！":WScript.Quit
Set fso=CreateObject("scripting.filesystemobject")
Set f=fso.GetFile(WScript.Arguments(0))
If Err Then WScript.Quit
If f.Size=0 Then WScript.Quit
'获取文件2进制代码：
Set stream=CreateObject("adodb.stream")
With stream
.Type=1:.Open:.LoadFromFile f
End With
bin=stream.Read(f.Size)
'生成bat：
cr=vbCrLf:n=&h100:line=1:seg=1:segeof=false:str=""
Set bat=fso.CreateTextFile(f.Path&".bat")
bat.WriteLine "@md %tmp%\t1.17&&pushd %tmp%\t1.17&&more <""%~f0"" +1|debug>nul&&popd&?/b %tmp%\t1.17\t* """&f.Name&"""&&rd/s/q %tmp%\t1.17&goto :eof"
For i=1 To Lenb(bin)
zero="":segeof=false:one=Ascb(Midb(bin,i,1))
If one<16 Then zero="0"
str=str&" "&zero& Hex(one)
If i Mod 16=0 Then bat.WriteLine "e"& Hex(n)&str:str="":n=n+16:line=line+1
If line Mod 4081=0 Then bat.WriteLine "n t"&seg&cr&"rcx"&cr&"ff00"&cr&"w":seg=seg+1:n=&h100:line=1:segeof=true
Next
If Not str="" Then bat.WriteLine "e"& Hex(n)&str
If Not segeof Then bat.WriteLine "n t"&seg&cr&"rcx"&cr& Hex(f.Size-(seg-1)*65280)&cr&"w"&cr&"q"
stream.Close:bat.Close
Set stream=Nothing:Set f=Nothing:Set bat=Nothing:Set fso=Nothing
WScript.Echo "Successful!"