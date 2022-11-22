# foreach

```cmake
foreach(<loop_var> <items>)
  <commands>
endforeach()

foreach(<loop_var> RANGE <stop>)
foreach(<loop_var> RANGE <start> <stop> [<step>])
foreach(<loop_var> IN [LISTS [<lists>]] [ITEMS [<items>]])
foreach(<loop_var>... IN ZIP_LISTS <lists>)


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

`item` 必须是列表