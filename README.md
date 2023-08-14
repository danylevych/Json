# **GUIDE**
- [How to include?](https://github.com/danylevych/Json/edit/master/README.md#how-to-include)
  - [As other project](https://github.com/danylevych/Json#as-other-project)
  - [As static lib](https://github.com/danylevych/Json#as-static-lib)



# **How to include?**
Firstly, you need to download files from this repository.
You can do this by two ways.<br> 
  ### First:
  - Copy the url.<br>
    ![](/assets/urlClone.png)
  
  - Open folder, that you need, and do the next.<br><br>
    ![](/assets/openCMD.png)
  
  - When the comand line opened, enter the next text.
    ```
    git clone https://github.com/danylevych/Json.git
    ```
    ![](/assets/enterCloneText.png)

  ### Second:
  - Download ZIP, and unpacked it.<br><br>
    ![](/assets/downloadZIP.png)




## **As other project**
  - After your downloading, go to the folder where Json repository is storing and copy only "Json" folder from there (it's more that enough). Than paste its in your project.<br><br>
    ![](/assets/pastingJson.png)<br><br><br>

  - Then go to Visual Studio (or program that you use), and add the Json project.<br><br>
    ![](/assets/addJsonToVS1.png)<br><br><br>
  
  - Than you need to add reference to Json project.<br><br>
    ![](/assets/addJsonToVS2.png)<br><br><br>
  
  - Now you can use "Json" as you need.<br><br>
    ![](/assets/addJsonToVS3.png)




## **As static lib**
  - First, that you need it is copy "include" and "lib" folders in directory where your project is.<br><br>
    ![](/assets/addJsonToVS4.png)<br><br><br>
  
  - Open Visual Studio. Go to "Properties", than "C/C++ -> Genaral -> Additional Include Directories", and add the path to "include" folder for the option.<br><br>
    ![](/assets/addJsonToVS5.png)<br><br><br>
  
  - Next step - in "Properties" go to "Linker -> General -> Additional Library Directories". Here you need to add the path to "lib" folder.<br><br>
    ![](/assets/addJsonToVS6.png)<br><br><br>
  
  - And last that you need is in "Linker" part go to "Input -> Additional Dependencies", and add the "JsonDebug.lib" and "JsonRelease.lib" at the option.<br>
    > [!WARNING]
    > For Release configuration add only "JsonRelease.lib", and for Debug, as you can guess, it's "JsonDebug.lib".
    <br>
    
    - Switch the configuration to "Debug" and add the "JsonDebug.lib".<br><br>
      ![](/assets/addJsonToVS7.png)<br><br><br>
    - Switch the configuration to "Release" and add the "JsonRelease.lib".<br><br>
      ![](/assets/addJsonToVS8.png)
  
  - Now you can use it as you need.
    ![](/assets/addJsonToVS9.png)
 


## **The next is How to work, so...**
