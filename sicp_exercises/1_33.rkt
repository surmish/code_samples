#!/usr/bin/racket
#lang racket/base

(define (filtered-accumulate filter combiner null-value term a next b)
  (cond ((> a b) null-value)
        ((filter a) (combiner (term a) (filtered-accumulate filter combiner null-value term (next a) next b)))
        (else (filtered-accumulate filter combiner null-value term (next a) next b))
        )
  )

(define (pi-sum a b)
  (filtered-accumulate true + 0 (lambda (x) (/ 1.0 (* x (+ x 2))))
                      a
                      (lambda (x) (+ x 4))
                      b)
  )


(define (integral f a b dx )
  (* (filtered-accumulate true + 0 f
                         (+ a (/ dx 2.0))
                         (lambda (x) (+ x dx))
                         b)
     dx)
  )

(define (true x) #t)
(define (cube x) (* x x x))
(define (square x) (* x x))
(define (pi-product-term a) (/ (* (* a 2.0) (* (+ a 1) 2)) (square (+ (* 2 a) 1))))
(define (inc a) (+ a 1))
(define (identity a) a)
(define (prime? n)
  (define (iter k)
    (cond ((> (square k) n) #t)
          ((= (remainder n k) 0) #f)
          (else (iter (inc k)))
          )
    )
  (if (or (= n 0) (= n 1))
      #f
      (iter 2))
  )

(printf "linear recursive sum of cubes(3): ~a\n" (filtered-accumulate true + 0 cube 1 inc 3))
(printf "linear recursive sum of integers(10): ~a\n" (filtered-accumulate true + 0 identity 1 inc 10))
(printf "linear recursive pi-sum (200000 terms): ~a\n" (* 8 (pi-sum 1 200000)))
(printf "linear recursive integral (dx = 0.0001): ~a\n" (integral cube 0 1 0.0001))
(printf "linear recursive factorial(5): ~a\n" (filtered-accumulate true * 1 identity 1 inc 5))
(printf "linear recursive pi-product: ~a\n" (* 4 (filtered-accumulate true * 1 pi-product-term 1 inc 10000)))

(define (gcd a b) 
  (cond ((= b 0) a)
        (else (gcd b (remainder a b) ))
        )
  )

(define (primeloop k n)
  (if (prime? k) (printf "~a\n" k) 0)
  (if (> k n)
      (printf "")
      (primeloop (+ k 1) n)
      )
  )

#| (primeloop 1 541) |#

(filtered-accumulate prime? + 0 square 1 inc 6)

(define (product-rel-primes n)
  (define (relatively-prime? k)
    (if (= (gcd k n) 1) #t #f))
  (filtered-accumulate relatively-prime? * 1 identity 1 inc n)
  )

(product-rel-primes 10)

#| (prime? 0) |#
#| (prime? 1) |#
#| (prime? 2) |#
#| (prime? 3) |#
#| (prime? 4) |#
#| (prime? 5) |#
#| (prime? 6) |#
#| (prime? 7) |#
#| (prime? 8) |#
#| (prime? 9) |#
#| (prime? 10) |#
