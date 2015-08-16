# LightSTL
LightSTL是STL的一个子集和一个超集，是我在分析STL源码后结合自己的理解进行编写的  
主要目的在于提高数据结构与算法和C++编程


## LightSTL开发进度
* 底层配置和主要容器
    * iterator_traits(100%)
    * type_traits(100%)
    * 空间配置器(100%)
    * functor(70%)
    * vector(100%)
    * list(100%)
    * queue(100%)
    * stack(100%)
    * pair(100%)
    * hash_table(100%)
    * hash_map(100%)
* 算法库
    * fill(100%)
    * fill_n(100%)
    * copy(100%)
    * copy_backward(100%)
    * sort(30%) 


## LightSTL单元测试（语句覆盖）
* 主要容器
    * vector(100%)
    * list(100%)
    * queue(100%)
    * stack(100%)
    * hash_table(100%)
    * hash_map(100%)
* 算法库
    * fill(100%)
    * fill_n(100%)
    * copy(100%)
    * copy_backward(100%) 


## LightSTL性能测试

### 测试环境： Ubuntu14.04 && gcc-4.8.2 && release模式 

### vector
(1)vector \<double\>
```cpp
//std::vector<double> vec   LightSTL::vector<double> vec 
clock_t t1 = clock(); 
for(int i = 0;i < TestSize;i++){ 
    vec.push_back(i); 
} 
clock_t t2 = clock(); 
printf("%lfms\n",(double)1000*(t2-t1)/CLOCKS_PER_SEC); 
```
测试结果：

|Container                 | TestSize |Time (ms)|
|--------------------------|---------:|--------:|
|LightSTL::vector\<double\>|      10^5|        2|
|LightSTL::vector\<double\>|      10^6|       15|
|LightSTL::vector\<double\>|      10^7|      114|
|std::vector\<double\>     |      10^5|        2|
|std::vector\<double\>     |      10^6|        9|
|std::vector\<double\>     |      10^7|       73|

(2)vector \<string\>
```cpp
//std::vector<std::string> vec  LightSTL::vector<std::string> vec
clock_t t1 = clock();
for(int i = 0;i < TestSize;i++){
    vec.push_back(std::string("Hello World"));
}
clock_t t2 = clock();
printf("%lfms\n",(double)1000*(t2-t1)/CLOCKS_PER_SEC);
```
测试结果：

|Container                      | TestSize |Time (ms)|
|-------------------------------|---------:|--------:|
|LightSTL::vector\<std::string\>|      10^5|       11|
|LightSTL::vector\<std::string\>|      10^6|       98|
|LightSTL::vector\<std::string\>|      10^7|      977|
|std::vector\<std::string\>     |      10^5|       10|
|std::vector\<std::string\>     |      10^6|       84|
|std::vector\<std::string\>     |      10^7|      916|


### list
(1)list \<double\>
```cpp
//std::list<double> lt   LightSTL::list<double> lt 
clock_t t1 = clock();
for(int i = 0;i < TestSize;i++){
    lt.push_back(i);
}
clock_t t2 = clock();
printf("%lfms\n",(double)1000*(t2-t1)/CLOCKS_PER_SEC);
```
测试结果：

|Container               | TestSize |Time (ms)|
|------------------------|---------:|--------:|
|LightSTL::list\<double\>|      10^5|        2|
|LightSTL::list\<double\>|      10^6|       13|
|LightSTL::list\<double\>|      10^7|      104|
|std::list\<double\>     |      10^5|        2|
|std::list\<double\>     |      10^6|       11|
|std::list\<double\>     |      10^7|       86|

(2)list \<string\>
```cpp
//std::list<std::string> lt   LightSTL::list<std::string> lt 
clock_t t1 = clock();
for(int i = 0;i < TestSize;i++){
    lt.push_back(std::string("Zhang Weiliang"));
}
clock_t t2 = clock();
printf("%lfms\n",(double)1000*(t2-t1)/CLOCKS_PER_SEC);
```
测试结果：

|Container                    | TestSize |Time (ms)|
|-----------------------------|---------:|--------:|
|LightSTL::list\<std::string\>|      10^5|       10|
|LightSTL::list\<std::string\>|      10^6|       88|
|LightSTL::list\<std::string\>|      10^7|      792|
|std::list\<std::string\>     |      10^5|       11|
|std::list\<std::string\>     |      10^6|       91|
|std::list\<std::string\>     |      10^7|      924|

(3)list.sort()
```cpp
srand((unsigned)time(0));
std::list<int> lt1;
LightSTL::list<int> lt2 ;
for(int i = 0;i < TestSize;i++){
    int tmp = rand();
    lt1.push_back(tmp);
    lt2.push_back(tmp);
}

clock_t t1 = clock();
lt1.sort();
clock_t t2 = clock();
printf("%lfms\n",(double)1000*(t2-t1)/CLOCKS_PER_SEC);

clock_t t3 = clock();
lt2.sort();
clock_t t4 = clock();
printf("%lfms\n",(double)1000*(t4-t3)/CLOCKS_PER_SEC);
```
测试结果：

|Container                 | TestSize |Time (ms)|
|--------------------------|---------:|--------:|
|LightSTL::list\<std::int\>|      10^5|       18|
|LightSTL::list\<std::int\>|      10^6|      336|
|LightSTL::list\<std::int\>|      10^7|     5113|
|std::list\<std::int\>     |      10^5|       22|
|std::list\<std::int\>     |      10^6|      372|
|std::list\<std::int\>     |      10^7|     6220|

### hash_table 
```cpp
LightSTL::hash_table<int> htb;
for(int i = 0;i < 2000000;i++){
      if(i == 7 || i == 46 || i == 9589)  continue;
      htb.insert_unique(i);
}
assert(htb.size() == 1999997);
LightSTL::hash_table<int>::iterator ite;
for(int i = 0;i < 2000000;i++){
      if(i == 7 || i == 46 || i == 9589)
            assert(htb.find(i) == htb.end());
      else    
            assert(*htb.find(i) == i);
}
