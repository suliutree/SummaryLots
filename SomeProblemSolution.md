问题1：std::string to std::wstring

  string str = "hello world";
  wstring wstr (str.begin(), str.end());
  
问题2：char* to std::wstring
  
  char* str = "hello worlddd";
  wstring wstr (str, str+strlen(str));
  
问题3：std::string to wchar_t*

  std::wstring widestr = std::wstring(str.begin(), str.end());
  wchar_t* widecstr = widestr.c_str();
  

  
