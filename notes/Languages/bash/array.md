# 数组

Shell 只支持一维数组，初始化时不需要定义数组大小

```sh
# 定义一个一般数组
declare -a array
# 为数组元素赋值
array[0]=1000
array[1]=2000
array[2]=3000
array[3]=4000
# 直接使用数组名得出第一个元素的值
echo $array
# 取数组所有元素的值
echo ${array[*]}
echo ${array[@]}
# 取第n个元素的值
echo ${array[0]}
echo ${array[1]}
echo ${array[2]}
echo ${array[3]}
# 数组元素个数
echo ${#array[*]}
# 取数组所有索引列表
echo ${!array[*]}
echo ${!array[@]}

array_name=(value1 value2 ... valuen)
my_array=(A B "C" D)
```