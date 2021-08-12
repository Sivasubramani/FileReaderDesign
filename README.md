# FileReaderDesign

Commands to install in mac:

Download build.zip from https://github.com/Sivasubramani/FileReaderDesign/

unzip build.zip
cd build
make install
cd build/bin/

Use case 1:
./FileReaderDesign filename.xxx 
ex: ./FileReaderDesign sample.fzz 

Use case 2a:
./FileReaderDesign filename.xxx encryption_format
ex: ./FileReaderDesign sample.fzz ENC_AES128

Use case 3:
./FileReaderDesign filename.xxx compression_format
ex1: ./FileReaderDesign sample.fzz COM_GZIP
ex2: ./FileReaderDesign sample.fzz COM_BZIP2

Use case 4:
./FileReaderDesign filename.xxx compression_format encryption_format 
ex1: ./FileReaderDesign sample.fzz COM_GZIP ENC_AES128
ex2: ./FileReaderDesign sample.fzz COM_BZIP2 ENC_AES128

Use case 5:
./FileReaderDesign filename.xxx decryption_format
ex: ./FileReaderDesign sample.fzz DEC_AES128

Use case 6:
./FileReaderDesign filename.xxx decompression_format
ex: ./FileReaderDesign sample.fzz DCOM_GZIP
ex2: ./FileReaderDesign sample.fzz DCOM_BZIP2

Use case 7:
./FileReaderDesign filename.xxx decompression_format decryption_format
ex1: ./FileReaderDesign sample.fzz DCOM_GZIP DEC_AES128
ex2: ./FileReaderDesign sample.fzz DCOM_BZIP2 DEC_AES128

