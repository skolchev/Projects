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

count3 x
 | x == 3 = 1
 | x < 10 = 0
 | otherwise = count3 ( div x 10 ) + if ( mod x 10 ) == 3 then 1 else 0

has3 x
 | x == 3 = True
 | x < 10 = False 
 | ( mod x 10 ) == 3 = True
 | otherwise = has3 ( div x 10 ) 

hask x k
 | x == k = True
 | x < 10 = False
 | ( mod x 10 ) == k = True
 | otherwise = hask ( div x 10 ) k

countk x k
 | x == k = 1
 | x < 10 = 0
 | otherwise = countk ( div x 10 ) k + if ( mod x 10 ) == k then 1 else 0


common x y  
 | x == y = True
 | x < 10 = hask y x
 | hask y ( mod x 10 ) = True
 | otherwise = common ( div x 10 ) y

duplicate x
 | x < 10 = False
 | hask ( div x 10 ) ( mod x 10 ) =  True
 | otherwise = duplicate ( div x 10 )

range a b
 | a == b = a
 | otherwise   = a + ( range ( a + 1 ) b ) * 10

len l
 | null l = 0
 | otherwise = len ( tail l) + 1

c3 l
 | null l = 0
 | head l  == 3 = c3 ( tail l) + 1
 | otherwise = c3 ( tail l )

ceven l
 | null l = 0
 | even ( head l ) = 1 + ceven ( tail l )
 | otherwise = ceven ( tail l )

sumeven l
 | null l = 0
 | even ( head l ) = head l + sumeven ( tail l )
 | otherwise = sumeven ( tail l )

haselem l x
 | null l = False
 | head l == x = True
 | otherwise = haselem ( tail l ) x

countelem l x
 | null l = 0
 | head l == x = countelem (tail l) x + 1
 | otherwise = countelem (tail l) x

commonl x y
 | null x = 0
 | null y = 0
 | haselem x (head y) = 1 + commonl x  (tail y)
 | otherwise = commonl x (tail y)


rep n x
 | n == 1 = 
 | otherwise = x:x + rep (n-1) x
range --
union -- spisyk s obshtite elementi
intersection
diff - 