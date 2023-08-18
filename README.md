# **GUIDE**
  - [How to include?](https://github.com/danylevych/Json/edit/master/README.md#how-to-include)
    - [As other project](https://github.com/danylevych/Json#as-other-project)
    - [As static lib](https://github.com/danylevych/Json#as-static-lib)
  - [Data types](https://github.com/danylevych/Json#data-types)
    - [Int](https://github.com/danylevych/Json#int)
    - [Float](https://github.com/danylevych/Json#float)
    - [Null](https://github.com/danylevych/Json#null)
    - [Boolean](https://github.com/danylevych/Json#boolean)
    - [String](https://github.com/danylevych/Json#string)
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
    > [!IMPORTANT]
    > For Release configuration add only `JsonRelease.lib`, and for Debug, as you can guess, it's `JsonDebug.lib`.
    <br>

    - Switch the configuration to `Debug` and add the `JsonDebug.lib`.<br><br>
      ![](/assets/includeImg/addJsonToVS7.png)<br><br><br>
    - Switch the configuration to `Release` and add the `JsonRelease.lib`.<br><br>
      ![](/assets/includeImg/addJsonToVS8.png)<br><br><br>
    
    - Now you can use it as you need.<br><br>
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
  <br>

  > [!IMPORTANT]
  > Each of the classes has one mhetod, that only return the reference, or const reference, to the value, that the class is storing - `SotoreValueType& Value()` or `const SotoreValueType& Value() const`.

  <br>Also we are going to talk about check's type methods. It is the `Core::Types::BaseType::IsSomeType()`, this mhetod return true if current instance has the same `type` like one that is in `SomeType` (for example: if we call the `Core::Types::BaseType::IsInt()`, it will return `true` if current instance store the `Core::Types::Int`, and `false` in oposite situation).

  ## **Int**

  The json's `int` or `number`, call it as you want, has represented as `Core::Types::Int` class. That is a wrapper for `int` type. So, you can yse it as default `int` variable.
  
  ### Mhetods

  | Mhetod's name | Description |
  | ------------- | ----------- |
  | `Int()` | Default cunstructer, that initialize `variavle` defult value - `0`. |
  | `Int(int value)` | Constructer, that takes one parameters `value`, that will be storing. |
  | `Int(const Int& ohter)` | Copy constructer. |
  | `Int(Int&& ohter) noexcept` | Move constructer. |
  | `Int& operator=(const Int& other)` | Assignment copy operator. |
  | `Int& operator=(Int&& other) noexcept` | Assigment move opertor. |
  |<br>|<br>|
  | `operator int&()` | Type cast operator, that returns the reference to the storing value. |
  | `operator const int&() const` | Type cast operator, that returns the const reference to the storing value. |
  | `operator int() const`| Type cast operator to `int` type |
  | `operator Int() const`| Type cast operator to `Core::Types::Int` type. |
  |<br>|<br>|
  | `virtual JsonTypes GetType() const` | Overloaded `Core::Types::BaseType`'s method, that returns a type of this class. (You can say, that is unuseless, but we will have seen it late :D) |
  |<br>|<br>|
  | `int& Value()` | Returns the reference to value which is inside in class. |
  | `const int& Value() const` | Returns the const reference to value which is inside in class. |

  
  <br>As the `Core::Types::Int` is a doughter calss from the `Core::Types::BaseTypes`, it has all methods, that `Core::Types::BaseTypes` has.
  <br>

  ## **Float**

  The `Core::Types::Float` is a class, that can store a fractional number. It's only a wrapper under `double` type.

  ### Mhetods

  | Mhetod's name | Description |
  | ------------- | ----------- |
  | `Float()` | Default cunstructer, that initialize `variavle` defult value - `0.0`. |
  | `Float(double value)` | Constructer, that takes one parameters `value`, that will be storing. |
  | `Float(const Float& ohter)` | Copy constructer. |
  | `Float(Float&& ohter) noexcept` | Move constructer. |
  | `Float& operator=(const Float& other)` | Assignment copy operator. |
  | `Float& operator=(Float&& other) noexcept` | Assigment move opertor. |
  |<br>|<br>|
  | `operator double&()` | Type cast operator, that returns the reference to the storing value. |
  | `operator const double&() const` | Type cast operator, that returns the const reference to the storing value. |
  | `operator double() const`| Type cast operator to `double` type |
  | `operator Float() const`| Type cast operator to `Core::Types::Float` type. |
  |<br>|<br>|
  | `virtual JsonTypes GetType() const` | Overloaded `Core::Types::BaseType`'s method, that returns a type of this class. (You can say, that is unuseless, but we will have seen it late :D) |
  |<br>|<br>|
  | `double& Value()` | Returns the reference to value which is inside in class. |
  | `const double& Value() const` | Returns the const reference to value which is inside in class. |

  <br>As the `Core::Types::Float` is a doughter calss from the `Core::Types::BaseTypes`, it has all methods, that `Core::Types::BaseTypes` has.
  <br>

  ## **Null**

  Json's files have the `null` type, so, the `Core::Types::Null` represent it in my class.

  ### Mhetods

  | Mhetod's name | Description |
  | ------------- | ----------- |
  | `Null()` | Default cunstructer, that initialize `variavle` defult value - `nullptr`. |
  |<br>|<br>|
  | `operator std::string&() const` | Type cast operator, that returns the instance of `std::string`, which look like `"null"`. |
  | `operator bool() const` | Type cast operator, that always returns `false`. |
  |<br>|<br>|
  | `virtual JsonTypes GetType() const` | Overloaded `Core::Types::BaseType`'s method, that returns a type of this class. (You can say, that is unuseless, but we will have seen it late :D) |
  |<br>|<br>|
  | `const std::nullptr_t& Value() const` | Returns the const reference to value which is inside in class. |
  |<br>|<br>|
  | `std::ostream& operator<<(std::ostream& out, const Null& null)` | The overloaded out operator. |

  <br>As the `Core::Types::Null` is a doughter calss from the `Core::Types::BaseTypes`, it has all methods, that `Core::Types::BaseTypes` has.
  <br>

  ## **Boolean**
  The `Core::Types::Boolean` represented `bool` type.

  ### Mhetods

  | Mhetod's name | Description |
  | ------------- | ----------- |
  | `Boolean()` | Default cunstructer, that initialize `variavle` defult value - `false`. |
  | `Boolean(bool value)` | Constructer, that takes one parameters `value`, that will be storing. |
  | `Boolean(const Boolean& ohter)` | Copy constructer. |
  | `Boolean(Boolean&& ohter) noexcept` | Move constructer. |
  | `Boolean& operator=(const Boolean& other)` | Assignment copy operator. |
  | `Boolean& operator=(Boolean&& other) noexcept` | Assigment move opertor. |
  |<br>|<br>|
  | `operator bool&()` | Type cast operator to `bool` reference. |
  | `operator const bool&() const` | Type cast operator to `bool` const reference. |
  | `operator bool() const` | Type cast operator, that return current state of `value`, it's can be `true` or `false`. |
  | `operator std::string() const` | Type cast operator, which return `std::string` instance, that look like `"true"` or `"false"` - it's depending of state `value` inside the current instance. |
  |<br>|<br>|
  | `virtual JsonTypes GetType() const` | Overloaded `Core::Types::BaseType`'s method, that returns a type of this class. (You can say, that is unuseless, but we will have seen it late :D) |
  |<br>|<br>|
  | `bool& Value()` | Returns the reference to value which is inside in class. |
  | `const bool& Value() const` | Returns the const reference to value which is inside in class. |
  |<br>|<br>|
  | `std::ostream& operator<<(std::ostream& out, const Boolean& boolean)` | The overloaded out operator. |

  <br>As the `Core::Types::Null` is a doughter calss from the `Core::Types::BaseTypes`, it has all methods, that `Core::Types::BaseTypes` has.
  <br>

  ## **String**

  So, now we are going to talk about `Core::Types::String`. This class is reptresenting json's `string`. The `Core::Types::String` is a wrapper under the `std::wstring`. 
  *Why is `std::wstring`, and not `std::string`?* 
  Because, the json can works with `utf 8` format of coding, so, I think, thet it was optimal to use `std::wstring`.

  ### Mhetods

  | Mhetod's name | Description |
  | ------------- | ----------- |
  | `String()` | Default cunstructer, that initialize `variavle` defult value - `false`. |
  | `String(const char* value)` | Constructer, that gets `const char*` values. |
  | `String(std::string&& value)` | Constructer, that gets r-value instances of `std::string`. |
  | `String(const std::string& value)` | Constructer, that gers l-value instance of `std::string`. |
  | `String(std::wstring&& value)` | Constructer, that gets r-value instances of `std::wstring`. |
  | `String(const std::wstring& value)` | Constructer, that gers l-value instance of `std::wstring`. |
  | `String(const String& other)`| Copy constructer. |
  | `String(String&& other)`| Move constructer. |
  | `String& operator=(const String& other)` | Assignment copy operator. |
  | `String& operator=(String&& other) noexcept` | Assigment move opertor. |
  |<br>|<br>|
  | `operator std::string() const` | Overloaded type cast operator to `std::string`. |
  | `operator std::wstring&()` | Overloaded type cast operator, which returns the reference to the value, that stored in the current instance of `Core::Types::String`. |
  | `operator const std::wstring&() const` | Overloaded type cast operator, which returns the const reference to the value, that stored in the current instance of `Core::Types::String`. |
  |<br>|<br>|
  | `virtual JsonTypes GetType() const` | Overloaded `Core::Types::BaseType`'s method, that returns a type of this class. (You can say, that is unuseless, but we will have seen it late :D) |
  |<br>|<br>|
  | `std::wstring& Value()` | Returns the reference to value which is inside in class. |
  | `const std::wstring& Value() const` | Returns the const reference to value which is inside in class. |
  |<br>|<br>|
  | `bool operator<(const String& other) const` | Overloaded less operator. |
  | `bool operator>(const String& other) const` | Overloaded greater operator. |
  | `bool operator!=(const String& other) const` | Overloaded equal operator. |
  | `bool operator==(const String& other) const` | Overloaded not equal operator. |
  |<br>|<br>|
  | `std::ostream& operator<<(std::ostream& out, const String& string)` | The overloaded out operator. Its returs the `std::ostream&` that has a string like in json - `"some text"`. |

  <br>As the `Core::Types::String` is a doughter calss from the `Core::Types::BaseTypes`, it has all methods, that `Core::Types::BaseTypes` has.
  <br>

  ## **Array**

  Now, we will talking, about something interesting, this is a `Core::Types::Array`.
  
  `Core::Types::Array` is a class that, can store a set of each types, that is here. And if i say 'all' it's mean all, including itself, and `Core::Types::Object`(this is the next, and finaly data type that we need to talk, but it will be later).

  As I said it can store all data types, and it can do this because of it is a wrapper under `std::vector<std::unique_ptr<Core::Types::BaseType>>`. It saves the poiters into all values, so we can do down cast ad get the type, which we need.

  First that I need to explain is all aliases.
  - `BaseTypePtrT` - is the aliase of `Core::Types::BaseType*`
  - `BaseSmartPtrT` - is the aliase of `std::unique_ptr<Core::Types::BaseType>`

  Simply?

  I can talk to you a lot of story of this class, but let's go to view methods that are in its, and after this I will show some exanples.

  Sooooooo, let's go.

  ### Mhetods
  
  | Mhetod's name | Description |
  | ------------- | ----------- |
  | `Array()` | Default constructer. |
  | `Array(const std::initializer_list<BaseTypePtrT>& list)` | Constructer, that gets a list of raw pointers as parameters ([Example]()), i guss that it will be the most usefull, and common method. |
  | `Array(Array&& other) noexcept` | Move constructer. |
  
  >[!IMPORTANT]
  > The `Core::Types::Array` doesn't have a copy constucter, oh no, this type of cunstructer deleted, such as we are working with the pointers. 
  >
  > Yep, you can ask, "we can copy values of each element not an address, so why do not you do it?". 
  >
  > Simply, I am not to do it because I like procrastination. Don't worry, maybe I do it as fast as I can.
  
  | Mhetod's name | Description |
  | ------------- | ----------- |
  | | |