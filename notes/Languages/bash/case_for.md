# case for

`case` 分支和 `for` 循环不再是判断表达式是否为真，而是去匹配字符串

## case

```sh
case word in [ [(] pattern [ | pattern ] ... ) list ;; ] ... esac
# 等同于
case $1 in
        pattern)
        list
        ;;
        pattern)
        list
        ;;
        pattern)
        list
        ;;
esac
# ;; 表示 break

case $1 in
	(zorro)
	echo "hello zorro!"
	;;
	(jerry)
	echo "hello jerry!"
	;;
	(*)
	echo "get out!"
	;;
esac

case $1 in
	zorro)
	echo "hello zorro!"
	;;
	jerry)
	echo "hello jerry!"
	;;
	*)
	echo "get out!"
	;;
esac

case $1 in
	zorro|jerry)
	echo "hello $1!"
	;;
	*)
	echo "get out!"
	;;
esac
```

`case` 不仅仅可以匹配一个固定的字符串，还可以利用 `pattern` 做到一定程度的模糊匹配

bash 常见的通配符有三个：

- `?` 表示任意一个字符

- `*` 表示任意长度任意字符，包括空字符

- `[…]` 表示这个范围中的任意一个字符

## for

```sh
for name [ [ in [ word ... ] ] ; ] do list ; done

for i in 1 2 3 4 5;do echo $i;done
for i in /etc/*;do echo $i;done

for (( expr1 ; expr2 ; expr3 )) ; do list ; done
for ((count=0;count<100;count++))
do
	echo $count
done
```