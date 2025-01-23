cat data.dat | wc --lines
cat data.dat | grep d[ao]lor | wc --lines
cat data.dat | wc --words
cat data.dat | grep -o '\bmol[a-zA-Z]*' | wc --lines
