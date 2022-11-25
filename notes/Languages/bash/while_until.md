# while until

## while

```sh
while list-1; do list-2; done
# 等同于
while list-1
do
	list-2
done

count=0
while [ $count -le 100 ]
do
	echo $count
	count=$[$count+1]
done
```

## until

执行一系列命令直至条件为 true 时停止

```sh
until list-1; do list-2; done
# 等同于
until list-1
do
	list-2
done

count=0
until ! [ $count -le 100 ]
do
	echo $count
	count=$[$count+1]
done
```