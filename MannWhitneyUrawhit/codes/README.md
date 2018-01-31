#Mann-Whitney U Test
-Add to python path to the directory where the MannWhitneytest

```export PYTHONPATH=$PYTHONPATH:${PATH to directory containing MannWhitneyUtest.py}```


in your script:
```
import ROOT
import MannWhitneyUtest

U = MannWhitneyUtest(h1, h2)

#where h1 and h2 are TH1s
```
