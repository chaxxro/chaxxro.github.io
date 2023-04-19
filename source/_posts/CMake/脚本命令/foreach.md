---
toc:
  enable: true
  number: false
  max_depth: 3
title: foreach
date: 2023-04-18 21:02:32
tags: cmake
categories: cmake
---

```cmake
foreach(<loop_var> <items>)
  <commands>
endforeach()
```

`items` 是一系列用空格或分号分隔的列表，使用时需要写成 `${A}`

支持 `break` 和 `continue`

```cmake
# 指明下标条件
foreach(<loop_var> RANGE <stop>)
foreach(<loop_var> RANGE <start> <stop> [<step>])

# lists 必须是用空格或分号分割的一系列列表变量，使用时不需要 ${A}
foreach(<loop_var> IN [LISTS [<lists>]] [ITEMS [<items>]])

set(A 0;1)
set(B 2 3)
set(C "4 5")
set(D 6;7 8)
set(E "")
foreach(X IN LISTS A B C D E)
    message(STATUS "X=${X}")
endforeach()
#-- X=0
#-- X=1
#-- X=2
#-- X=3
#-- X=4 5
#-- X=6
#-- X=7
#-- X=8

foreach(<loop_var>... IN ZIP_LISTS <lists>)

list(APPEND English one two three four)
list(APPEND Bahasa satu dua tiga)

foreach(num IN ZIP_LISTS English Bahasa)
    message(STATUS "num_0=${num_0}, num_1=${num_1}")
endforeach()

foreach(en ba IN ZIP_LISTS English Bahasa)
    message(STATUS "en=${en}, ba=${ba}")
endforeach()

#-- num_0=one, num_1=satu
#-- num_0=two, num_1=dua
#-- num_0=three, num_1=tiga
#-- num_0=four, num_1=
#-- en=one, ba=satu
#-- en=two, ba=dua
#-- en=three, ba=tiga
#-- en=four, ba=
```