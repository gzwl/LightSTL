# LightSTL
LightSTL是STL的一个子集和一个超集，是我在分析STL源码后结合自己的理解进行编写的  
主要目的在于提高数据结构与算法和C++编程

## LightSTL开发进度
* 底层配置和主要容器
    * iterator_traits(100%)
    * type_traits(100%)
    * 空间配置器(100%)
    * vector(100%)
    * list(100%)
* 算法库
    * fill(100%)
    * fill_n(100%)
    * copy(100%)
    * sort(10%) 

## LightSTL性能测试

### vector
(1)vector \<int\>
```cpp
//std::vector<double> vec   LightSTL::vector<double> vec 
clock_t t1 = clock();
for(int i = 0;i < test_size;i++){
    vec.push_back(i);
}
clock_t t2 = clock();
printf("%lfms\n",(double)1000*(t2-t1)/CLOCKS_PER_SEC);
```
测试结果：

![](https://github.com/gzwl/Image/blob/master/vectortest1.png)

(2)vector \<string\>
```cpp
//std::vector<std::string> vec  LightSTL::vector<std::string> vec
clock_t t1 = clock();
for(int i = 0;i < test_size;i++){
    vec.push_back(std::string("Hello World"));
}
clock_t t2 = clock();
printf("%lfms\n",(double)1000*(t2-t1)/CLOCKS_PER_SEC);
```
测试结果：

![](https://github.com/gzwl/Image/blob/master/vectortest2.png)


### list
(1)list \<int\>
```cpp
//std::list<int> lt   LightSTL::list<int> lt 
clock_t t1 = clock();
for(int i = 0;i < test_size;i++){
    lt.push_back(i);
}
clock_t t2 = clock();
printf("%lfms\n",(double)1000*(t2-t1)/CLOCKS_PER_SEC);
```
测试结果：

![](https://github.com/gzwl/Image/blob/master/ListTest1.png)

(1)list \<string\>
```cpp
//std::list<std::string> lt   LightSTL::list<std::string> lt 
clock_t t1 = clock();
for(int i = 0;i < test_size;i++){
    lt.push_back("Zhang Weiliang");
}
clock_t t2 = clock();
printf("%lfms\n",(double)1000*(t2-t1)/CLOCKS_PER_SEC);
```
测试结果：

![](https://github.com/gzwl/Image/blob/master/ListTest2.png)
