#!/usr/bin/racket
#lang racket/base

; recursive process (and procedure)
(define (f n)
  (cond
   ((< n 3) n)
   (else (+ (f (- n 1))
            (* 2 (f (- n 2)))
            (* 3 (f (- n 3)))
            )
         )
   )
  )

; linear iterative process (uses recursive procedure f_iter)
(define (f_alt n)
  (define (f_iter a b c count)
    (cond 
      ((< count 0) count)
      ((= count 0) a)
      ((= count 1) b)
      ((= count 2) c)
      (else (f_iter b c (+ c (* 2 b) (* 3 a)) (- count 1))))
    )
   (f_iter 0 1 2 n)
  )

(printf "recursive process results:\n")
(f -1)
(f 0)
(f 1)
(f 2)
(f 3)
(f 4)
(f 5)
(f 6)
(f 7)
(f 8)
(f 9)
(f 10)

(printf "linear iterative process results:\n")
(f_alt -1)
(f_alt 0)
(f_alt 1)
(f_alt 2)
(f_alt 3)
(f_alt 4)
(f_alt 5)
(f_alt 6)
(f_alt 7)
(f_alt 8)
(f_alt 9)
(f_alt 10)
