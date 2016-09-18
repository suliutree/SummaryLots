<br>
问题1：std::string to std::wstring

  string str = "hello world";<br>
  wstring wstr (str.begin(), str.end());<br>

<br>
问题2：char* to std::wstring
  
  char* str = "hello worlddd";<br>
  wstring wstr (str, str+strlen(str));<br>

<br>  
问题3：std::string to wchar_t*

  std::wstring widestr = std::wstring(str.begin(), str.end());<br>
  wchar_t* widecstr = widestr.c_str();<br>
  

  
