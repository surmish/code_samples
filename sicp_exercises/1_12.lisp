#!/usr/bin/racket
#lang racket/base

(define (pascal_value row column)
  (cond ((< row 0) 0)
        ((< column 0) 0)
        ((= column 1) 1)
        ((= column row) 1)
        ((> column row) 0)
        (else (+ (pascal_value (- row 1) (- column 1)) (pascal_value (- row 1) column )))
        )
  )

(pascal_value 6 4)

(define (pascal_triangle max_rows)
  (define (print_pascal row column)
    (cond
     ((> row max_rows) (printf "done\n"))
     (else (cond ((= column row) (printf "~a\n" (pascal_value row column)) (print_pascal (+ row 1) 1))
                 (else (printf "~a " (pascal_value row column)) (print_pascal row (+ column 1)))))
     ))
  (print_pascal 1 1)
  )

(pascal_triangle 25)
