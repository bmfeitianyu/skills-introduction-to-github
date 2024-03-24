# 插入排序
add_executable(4-1InsertSort 01.InsertSort/main.c sortHelper.c sortHelper.h
        01.InsertSort/insertSort.c 01.InsertSort/insertSort.h)
# 交换排序
add_executable(4-2SwapSort 02.SwapSort/main.c sortHelper.c sortHelper.h
        02.SwapSort/bubbleSort.c 02.SwapSort/bubbleSort.h
        02.SwapSort/quickSort.c 02.SwapSort/quickSort.h)