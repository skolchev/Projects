fact x = if x > 0 then ( fact ( x - 1 ) * x ) else 1
factn x = if x > 0 then ( x * factn ( x - 1 ) ) else if x == 0 then 1 else (- factn ( -x ))
nroots a b c
 |d > 0 = 2
 |d == 0 = 1
 |otherwise  = 0
 where d = b*b - 4 * a * c
ndigits x
 | x < 10 = 1
 | x > 0 = ndigits(div x 10) + 1
sumdigits x
 | x < 10 = x
 | x > 0 = sumdigits ( div x 10 ) + mod x 10 
/* c3 x
 | x == 3 = 1
 | ( x < 10 ) = 0
 | otherwise = c3 ( div x 10 ) + (if ( mod x 10 ) == 3 then 1) */