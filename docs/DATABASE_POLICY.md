# DATABASE Public vs Private Policy

Dokumen ini menetapkan batas aman untuk folder `DATABASE` di repo public PAHLAWAN ROLEPLAY.

## Tujuan

- menjaga migration dan schema yang aman tetap dapat direview
- mencegah dump, backup, data user nyata, dan credential masuk repo public
- memberi acuan tunggal untuk maintainer dan kontributor saat review PR

## Boleh Ada di Repo Public

- file schema SQL yang hanya mendefinisikan struktur database
- file migration SQL yang hanya berisi perubahan schema atau data dummy yang aman
- example SQL atau seed contoh yang memakai placeholder aman
- fixture dummy atau test data sintetis yang tidak berasal dari data user nyata

## Tidak Boleh Ada di Repo Public

- dump database asli dari local, staging, atau production
- backup database dalam bentuk apa pun
- export data user nyata, termasuk akun, inventory, IP, log, atau data operasional privat
- file yang berisi username, password, DSN, token, API key, atau credential lain
- snapshot private, hasil debug database, atau file sementara yang memuat data sensitif

## Aturan Review

- anggap semua file baru di `DATABASE/` sebagai sensitif sampai terbukti aman
- jika file berisi data nyata atau asal-usulnya tidak jelas, jangan merge ke repo public
- gunakan placeholder atau data sintetis untuk contoh dan fixture
- jika perlu perubahan docs lintas repo, selaraskan dengan `README.md`, `SECURITY.md`, dan `CONTRIBUTING.md`

## Catatan Operasional

- policy ini tidak mengubah runtime behavior
- policy ini tidak mengubah schema, migration, atau isi file database yang sudah ada
- cleanup atau relokasi file database dilakukan hanya melalui issue atau PR terpisah
