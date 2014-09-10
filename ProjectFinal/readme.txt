i. 小組信息

本程序完全由 林馳 單獨製作,如有任何疑問請直接咨詢作者本人 
郵箱: 185191430@qq.com

ii. 文件列表

源代碼部分(位於FES_test文件夾中)

FES_test.pro		//QT工程文件
FSE_test.pro.user	//vs工程文件
fileset.cpp		//文件集合模塊
fileset.h
main.cpp		//主程序
serach.cpp		//搜索模塊(邏輯運算)
serach.h
textfile.cpp		//文件模塊
textfile.h
welcome.cpp		//控制台輸出的歡迎模塊  在gui中沒有仍和作用
welcome.h
widget.cpp		//QT窗口設計
widget.h
widget.ui		//QTui文件
wordtable.cpp		//單詞表模塊
wordtable.h

編譯好程序部分(位於FSE3.0文件夾中)

自己使用的測試數據(位於PT文件夾中)

最終報告(finalreport.docx)

自述文件(readme.txt)
 
iii. 編譯方法 

編譯環境:
QTCreator 3.0.1
Based on Qt 5.2.1 (MSVC 2010, 32bit)
下載地址:
http://qt-project.org/downloads

配置后使用QTCreator打開FSE_test.pro文件即可導入  按ctrl+r進行編譯

iv. 執行方法

雙擊FSE3.0文件夾中的FSE_test.exe即可直接運行
若通過Gmail發送則需要將文件FSE_test更名為FSE_test.exe后運行

v. 已知bug

若文本文件中出現製表符,則會因為QT顯示的原因製表符部分為亂碼.因為是QT組件顯示的原因,因此無法對此bug進行修復.

