reduce = (fn, acc, [head, ...tail]) => head === undefined ?
  acc : reduce(fn, fn(acc, head), tail);

b = [1,2,3,4];
start = 10;
reduce((x, y) => x + y, start, b);
