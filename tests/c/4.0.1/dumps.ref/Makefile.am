include $(top_srcdir)/config/automake.common

SUFFIXES = .med .dump

.med.dump:
	@H5DUMP@ $< > $@

test2.dump: test2.med
	@H5DUMP@ -a /ENS_MAA/maa1/DIM -a /ENS_MAA/maa1/DES -a /ENS_MAA/maa1/TYP -g /ENS_MAA/maa2 -g /ENS_MAA/maa3 -g /INFOS_GENERALES $< > $@

#BUILT_SOURCES = 

check-local:\
./test10_mem_int.dump\
./test10_mem_ext_int.dump\
./test10_mem_long.dump\
./test10_mem_ext_long.dump\
./test10_int.dump\
./test10_long.dump\
./test10_f32_int.dump\
./test10_f32_long.dump\
./test10_f32_i32_long.dump\
./test10_f32_i64_long.dump\
./test10_i32_long.dump\
./test10_i64_long.dump\
./test10_f32_i32_int.dump\
./test10_f32_i64_int.dump\
./test10_i32_int.dump\
./test10_i64_int.dump\
./test12.dump\
./test14.dump\
./test16.dump\
./test18.dump\
./test19.dump\
./test1.dump\
./test20.dump\
./test21.dump\
./test23.dump\
./test25.dump\
./test27.dump\
./test29.dump\
./test31.dump\
./test2.dump\
./test4.dump\
./test6.dump\
./test8.dump



CLEANFILES = \
./test12.dump\
./test10_mem_int.dump\
./test10_mem_ext_int.dump\
./test10_mem_long.dump\
./test10_mem_ext_long.dump\
./test10_int.dump\
./test10_long.dump\
./test10_f32_int.dump\
./test10_f32_long.dump\
./test10_f32_i32_long.dump\
./test10_f32_i64_long.dump\
./test10_i32_long.dump\
./test10_i64_long.dump\
./test10_f32_i32_int.dump\
./test10_f32_i64_int.dump\
./test10_i32_int.dump\
./test10_i64_int.dump\
./test14.dump\
./test16.dump\
./test18.dump\
./test19.dump\
./test1.dump\
./test20.dump\
./test21.dump\
./test23.dump\
./test25.dump\
./test27.dump\
./test29.dump\
./test31.dump\
./test2.dump\
./test4.dump\
./test6.dump\
./test8.dump

EXTRA_DIST = \
./test12.med\
./test10_mem_int.med\
./test10_mem_ext_int.med\
./test10_mem_long.med\
./test10_mem_ext_long.med\
./test10_int.med\
./test10_long.med\
./test10_f32_int.med\
./test10_f32_long.med\
./test10_f32_i32_long.med\
./test10_f32_i64_long.med\
./test10_i32_long.med\
./test10_i64_long.med\
./test10_f32_i32_int.med\
./test10_f32_i64_int.med\
./test10_i32_int.med\
./test10_i64_int.med\
./test14.med\
./test16.med\
./test18.med\
./test19.med\
./test1.med\
./test20.med\
./test21.med\
./test23.med\
./test25.med\
./test27.med\
./test29.med\
./test31.med\
./test2.med\
./test4.med\
./test6.med\
./test8.med\
./test10-med.hdf\
./test2-med.hdf

EXTRA_DIST+= \
./test11b_.out\
./test11_.out\
./test11_test10_f32_i32.med.out\
./test11_test10_f32_i64.med.out\
./test11_test10_f32.med.out\
./test11_test10_i32.med.out\
./test11_test10_i64.med.out\
./test13_test12.med.out\
./test13b_test12.med.out\
./test15_test14.med.out\
./test17_.out\
./test22_.out\
./test24_.out\
./test26_.out\
./test28_.out\
./test30_test29.med.out\
./test32_test31.med.out\
./test33_test31.med.out\
./test3_.out\
./test5_.out\
./test7_.out\
./test9_.out

