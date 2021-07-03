#!/usr/bin/racket
#lang racket/base

(define (A x y)
  (cond ((= y 0) 0)
        ((= x 0) (* 2 y))
        ((= y 1) 2)
        (else (A (- x 1) (A x (- y 1))))))

(A 1 10) ; 1024
(A 2 4)  ; 65536
(A 3 3)  ; 65536

(define (f n) (A 0 n))
(define (g n) (A 1 n))
(define (h n) (A 2 n))
(define (k n) (* 5 n n))

(printf "function f[n] = 2*n \n") ; since x = 0 (for y != 0), the second test-expr is true and the body (* 2 y) is executed
(printf " f[0] is ~a\n" (f 0)) ; 0
(printf " f[1] is ~a\n" (f 1)) ; 2
(printf " f[2] is ~a\n" (f 2)) ; 4
(printf " f[3] is ~a\n" (f 3)) ; 6
(printf " f[4] is ~a\n" (f 4)) ; 8

(printf "function g[n] = 2^n \n") 
; A(1,n)  = 2*A(1,(n-1)) 
;         = 2*2*2*... [n-2 times] * A(1,(n-(n-2))) 
;         = 2^(n-2)*2*A(1,1) 
;         = 2^n for n > 0
(printf " g[0] is ~a\n" (g 0)) ; 0
(printf " g[1] is ~a\n" (g 1)) ; 2
(printf " g[2] is ~a\n" (g 2)) ; 4
(printf " g[3] is ~a\n" (g 3)) ; 8
(printf " g[4] is ~a\n" (g 4)) ; 16

(printf "function h[n] = 2^(2^(2^ ... n times)) \n") 
; A(2,n)  = A(1,A(2,(n-1))) 
;         = 2^A(2,(n-1)) 
;         = 2^A(1,A(2,(n-2)))
;         = 2^2^A(2,(n-2))
;         = 2^2...[n-2] times ^ A(2,(n-(n-2))) 
;         = 2^2^2....(n-2) times ^A(2,2)
;         = 2^2^2....(n-2) times ^ A(1,A(2,1))
;         = 2^2^2....(n-2) times ^ 2^2
;         = 2^2^2..... n times
(printf " h[0] is ~a\n" (h 0)) ; 0
(printf " h[1] is ~a\n" (h 1)) ; 2
(printf " h[2] is ~a\n" (h 2)) ; 4
(printf " h[3] is ~a\n" (h 3)) ; 16
(printf " h[4] is ~a\n" (h 4)) ; 65536

(printf "function k[n] = 5*n*n \n")
(printf " k[0] is ~a\n" (k 0)) ; 0
(printf " k[1] is ~a\n" (k 1)) ; 5
(printf " k[2] is ~a\n" (k 2)) ; 20
(printf " k[3] is ~a\n" (k 3)) ; 45
(printf " k[4] is ~a\n" (k 4)) ; 80
