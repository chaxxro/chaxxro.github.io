# select

`select` 提供给了一个构建交互式菜单程序的方式

```sh
select name [ in word ] ; do list ; done

select i in a b c d
do
	echo $i
done
# 显示
# 1) a
# 2) b
# 3) c
# 4) d
# 输入相应的数字索引，选择相应分支
# 如果输入的不是菜单描述的范围就会 echo 一个空行
# 如果直接输入回车，就会再显示一遍菜单本身
```

`select` 一般搭配 `case`

```sh
select i in a b c d
do
	case $i in
		a)
		echo "Your choice is a"
		;;
		b)
		echo "Your choice is b"
		;;
		c)
		echo "Your choice is c"
		;;
		d)
		echo "Your choice is d"
		;;
		*)
		echo "Wrong choice! exit!"
		exit
		;;
	esac
done
```