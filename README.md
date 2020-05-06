# FP SISOP20 E04

FP Sistem Operasi 2020\
Kelompok E 04

## 1. pwd
- Source code file: [pwd](https://github.com/segara2410/FP_SISOP20_E04/blob/master/pwd.c)
- `pwd` (menampilkan working directory)

## 2. head
- Source code file: [head](https://github.com/segara2410/FP_SISOP20_E04/blob/master/head.c)
- `head -n N file.txt` (mencetak isi file sebanyak N baris, default mencetak 10 baris tanpa option -n)
- `head -c N file.txt` (mencetak isi file sebanyak N byte pada baris pertama)
- `head -q file1.txt file2.txt ...` (digunakan jika file lebih dari 1, akan mencetak sebanyak 20 baris)
- `head -v file.txt` (selain mencetak 10 baris dari isi file, akan mencetak nama filenya pada baris pertama)

## 3. fold
- Source code file: [fold](https://github.com/segara2410/FP_SISOP20_E04/blob/master/fold.c)
- `fold -wN` (mencetak sebanyak N kolom)

## 4. cp
- Source code file: [cp](https://github.com/segara2410/FP_SISOP20_E04/blob/master/cp.c)
- `cp [file1] [file2]` (mengcopy file1 ke file2)
- `cp * [folder]` (mengcopy semua file di working directory ke folder)
- `cp -r [folder1] [folder2]` (mengcopy folder1 ke folder2)

## 5. mv
- Source code file: [mv](https://github.com/segara2410/FP_SISOP20_E04/blob/master/mv.c)
- `mv [file1] [file2]` (memindah file1 ke file2)
- `mv * [folder]` (memindah semua file di working directory ke folder)