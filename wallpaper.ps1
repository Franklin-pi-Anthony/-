# 打开指定目录
Start-Process explorer.exe -ArgumentList "C:\Users\ios23\AppData\Local\Packages\Microsoft.Windows.ContentDeliveryManager_cw5n1h2txyewy\LocalState\Assets"

# 获取目录中的所有文件
$files = Get-ChildItem "C:\Users\ios23\AppData\Local\Packages\Microsoft.Windows.ContentDeliveryManager_cw5n1h2txyewy\LocalState\Assets"

# 为每个文件添加 .bmp 后缀
foreach ($file in $files) {
    # 确保文件没有扩展名后缀
    if ($file.Extension -eq "") {
        $newName = $file.FullName + ".bmp"
        Rename-Item -Path $file.FullName -NewName $newName
    }
}
