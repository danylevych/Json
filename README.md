# **GUIDE**
- [How to include?](https://github.com/danylevych/Json/edit/master/README.md#how-to-include)
  - [As other project](https://github.com/danylevych/Json#as-other-project)
  - [As static lib](https://github.com/danylevych/Json#as-static-lib)
- [Data types]()
  - [Int]()
  - [Float]()
  - [Null]()
  - [Boolean]()
  - [String]()
  - [Array]()
  - [Object]()



# **How to include?**
Firstly, you need to download files from this repository.
You can do this by two ways.<br> 
  ### First:
  - Copy the url.<br>
    ![](/assets/includeImg/urlClone.png)
  
  - Open folder, that you need, and do the next.<br><br>
    ![](/assets/includeImg/openCMD.png)
  
  - When the comand line opened, enter the next text.
    ```
    git clone https://github.com/danylevych/Json.git
    ```
    ![](/assets/includeImg/enterCloneText.png)

  ### Second:
  - Download ZIP, and unpacked it.<br><br>
    ![](/assets/includeImg/downloadZIP.png)




## **As other project**
  - After your downloading, go to the folder where Json repository is storing and copy only `Json` folder from there (it's more that enough). Than paste its in your project.<br><br>
    ![](/assets/includeImg/pastingJson.png)<br><br><br>

  - Then go to Visual Studio (or program that you use), and add the Json project.<br><br>
    ![](/assets/includeImg/addJsonToVS1.png)<br><br><br>
  
  - Than you need to add reference to Json project.<br><br>
    ![](/assets/includeImg/addJsonToVS2.png)<br><br><br>
  
  - Now you can use `Json` as you need.<br><br>
    ![](/assets/includeImg/addJsonToVS3.png)




## **As static lib**
  - First, that you need it is copy `include` and `lib` folders in directory where your project is.<br><br>
    ![](/assets/includeImg/addJsonToVS4.png)<br><br><br>
  
  - Open Visual Studio. Go to `Properties`, than `C/C++ -> Genaral -> Additional Include Directories`, and add the path to `include` folder for the option.<br><br>
    ![](/assets/includeImg/addJsonToVS5.png)<br><br><br>
  
  - Next step - in `Properties` go to `Linker -> General -> Additional Library Directories`. Here you need to add the path to `lib` folder.<br><br>
    ![](/assets/includeImg/addJsonToVS6.png)<br><br><br>
  
  - And last that you need is in `Linker` part go to `Input -> Additional Dependencies`, and add the `JsonDebug.lib` and `JsonRelease.lib` at the option.<br>
    > [!WARNING]
    > For Release configuration add only `JsonRelease.lib`, and for Debug, as you can guess, it's `JsonDebug.lib`.
    <br>
    
    - Switch the configuration to `Debug` and add the `JsonDebug.lib`.<br><br>
      ![](/assets/includeImg/addJsonToVS7.png)<br><br><br>
    - Switch the configuration to `Release` and add the `JsonRelease.lib`.<br><br>
      ![](/assets/includeImg/addJsonToVS8.png)
  
  - Now you can use it as you need.
    ![](/assets/includeImg/addJsonToVS9.png)
 


# **Data types**
  **Files with json extention can store the next data types:**
  - Int
  - Float
  - Null
  - Boolean
  - String
  - Array
  - Object

  <br>So, dicided to create each of this class for the comfortable work.<br>
  
  **First that we need, it to see the hierarchy for them.**<br>
  
	Core::Types::BaseType ---|
				 |----> Core::Types::Int
	                         |----> Core::Types::Float
	                         |----> Core::Types::Null
	                         |----> Core::Types::Boolean
	                         |----> Core::Types::String
	                         |----> Core::Types::Array
	                         |----> Core::Types::Object

 
  <br>As you can see each of them is a daughter class of the `Core::Types::BaseType`.<br><br>


**What is Core::Types::BaseType?**<br><br>

  The `Core::Types::BaseType` is a parent class. For it we can do somenthing like dynamic typization(if we can named it like that) for our project.
  It has some virtual methods, such as `GetType()` and `Destructor`. It also has a protected field - `type`, which store the type of the current instance. In the below section you can see how `Core::Types::BaseType` look like.
   ```cpp
	namespace Core
	{
		namespace Types
		{
			class BaseType
			{
			protected:
				JsonTypes type;
	
			public:
				BaseType(JsonTypes&& type);
				BaseType(const JsonTypes& type);
			
			public:
				bool IsObject() const;
				bool IsArray() const;
				bool IsString() const;
				bool IsInt() const;
				bool IsFloat() const;
				bool IsBoolean() const;
				bool IsNull() const;
	
			public:
				template<typename T>
				T& Get() { return *dynamic_cast<T*>(this); }
	
			public:
				virtual JsonTypes GetType() const = 0;
				virtual ~BaseType() = default;
			
			};
		}
	}
   ```
  <br>`Core::Types::BaseType` also has the template method `Get<T>()`, that can parse instance to data type that you send its. It use for the down casting, and it will be show later.
  
  <br>Now is the time to talk about `type` field. As you can see, this field has a `Core::JsonTypes`. This is enumeration, which store names of all those types, that we were talking before.
   ```cpp
	namespace Core
	{
		enum class JsonTypes
		{
			Object = 1,
			Array,
			String,
			Int,
			Float,
			Boolean,
			Null
		};
	}
   ```

  <br>Also we are going to talk about check's type methods. It is the `Core::Types::BaseType::Is_____()`, this mhetod return true if current instance has the same `type` like one that is in `_____` (for example: if we call the  `Core::Types::BaseType::IsInt()`, it will return `true` if current instance store the `Core::Types::Int`, and `false` in oposite situation).




















