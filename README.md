# **GUIDE**
- How to include?
  - As other project
  - As static lib

# **How to include?**
Firstly, you need to download files from this repository.
You can do this by two ways.<br> 
### First:
- Copy the url.<br> 
![](/assets/urlClone.png)

- Open folder, that you need, and do the next.<br> 
![](/assets/openCMD.png)

- When the comand line opened, enter the next text.
```
git clone https://github.com/danylevych/Json.git
```
![](/assets/enterCloneText.png)

### Second:
- Download ZIP, and unpacked it.<br> 
![](/assets/downloadZIP.png)

## **As other project**
- After your downloading, go to the folder where Json repository is storing and copy only "Json" folder from there (it's more that enough). Than paste its in your project.<br>
![](/assets/pastingJson.png)

- Then go to Visual Studio (or program that you use), and add the Json project.<br>
![](/assets/addJsonToVS1.png)<br><br>

- Than you need to add reference to Json project.<br>
![](/assets/addJsonToVS2.png)<br><br>

- Now you can use "Json" as you need.<br>
![](/assets/addJsonToVS3.png)


## **As static lib**

- First, that you need it is copy "include" and "lib" folders in directory where your project is.<br>
![](/assets/addJsonToVS4.png)

- Open Visual Studio. Go to "Properties", than "C/C++ -> Genaral -> Additional Include Directories", and add the path to "include" folder for the option.<br>
![](/assets/addJsonToVS5.png)<br><br>

- Next step - in Properties go to Linker -> General -> Additional Library Directories. Here you need to add the path to "lib" folder.<br>
> **Warning**
> Remember, that the "lib" folder consist of two folders, it's "Debug" and "Release", choose one that you need. I know that is no comfortable to always swich the folder, but I have not any idea how to do it in one .lib. So, I'm sorry.
![](/assets/addJsonToVS6.png)

- And last that you need is in "Linker" part go to "Input -> Additional Dependencies", and add the "Json.lib" at the option.<br>
> **Note**
> For Debug and Release configuration the library has the same name.
![](/assets/addJsonToVS7.png)

## **The next is How to work, so...**
