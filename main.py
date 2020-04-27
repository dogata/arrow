# Interfacing between Python and C++
# ref: https://towardsdatascience.com/a-gentle-introduction-to-apache-arrow-with-apache-spark-and-pandas-bb19ffe0ddae

import numpy as np
import pandas as pd
import pyarrow as pa

df = pd.DataFrame({'one': [20, np.nan, 2.5],'two': ['january', 'february', 'march'],'three': [True, False, True]},index=list('abc'))

table = pa.Table.from_pandas(df)

print(table)