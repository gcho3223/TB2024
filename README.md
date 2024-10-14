# Code for EM Study

## Reference

### Base code

```bash
git clone git@github.com:swkim95/TB2024.git -b TB2024_centos
```

### ntuples

```
/pnfs/knu.ac.kr/data/cms/store/user/sungwon/2024_DRC_TB_ntuple
```

### physics runs

* [google sheet](https://docs.google.com/spreadsheets/d/1H2w0b0rfcMFYRcDRZUMS6uL91V1MmawK/edit?usp=sharing&ouid=117548372861877042914&rtpof=true&sd=true)

## Recipe (under centOS)

### first setup

```bash
git clone git@github.com:KyeongPil-Lee/TB2024.git -b EMStudy
cd TB2024
source buildNinstall_centos.sh
source envset_centos.sh
```

### after the first setup

```bash
source envset_centos.sh
# -- compile a code
./compile_centos.sh TBanalysis_ex
```





