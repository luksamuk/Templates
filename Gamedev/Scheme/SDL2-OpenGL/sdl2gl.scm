;;; Eggs you should install:
;;; - sdl2
;;; - opengl
;;; - loops
;;; - defstruct

(use (prefix sdl2 sdl2:))     ; SDL2
(require-extension gl)        ; OpenGL
(require-extension loops)     ; Loops such as do-while
(require-extension defstruct) ; Structs
;;(require-extension define-structure)

;;; Just because.
;;(repl-prompt (lambda () "* > "))


;;; Global variables
(define window #f)
(define gl-context #f)
(define running #t)
(define viewport-width 800)
(define viewport-height 600)


;; FPS-related
(define last-time 0)
(define fps-last-prompt-time 0)
(define fps-prompt-delay-interval 2000) ; 2 secs

;; Input variables
(defstruct input-values up down left right)
(define p1-input-state
  (make-input-values
   up:    #f
   down:  #f
   left:  #f
   right: #f))


;; Game variables
(defstruct vec2 x y)
(define sq-position
  (make-vec2
   x: (/ viewport-width 2.0)
   y: (/ viewport-height 2.0)))
(define rotation 0.0)
(define sq-size 200.0)


;;; Initialization func
(define (init)
  ;; Disables VSync
  (set! (sdl2:gl-swap-interval) 0)
  ;; Sets clear color
  (gl:ClearColor 0.0 0.0 0.0 1.0)

  ;; Define our orthographic view
  (gl:MatrixMode gl:PROJECTION)
  (gl:LoadIdentity)
  (gl:Ortho 0 viewport-width viewport-height 0 -1 1)
  (gl:MatrixMode gl:MODELVIEW))


(define (load-content)
  #t)


(define (unload-content)
  #t)

;;; Update func
(define (update delta-t)
  ;; Square rotation
  (set! rotation (+ rotation (* 30.0 delta-t)))
  (if (>= rotation 360.0)
      (set! rotation (- rotation 360.0)))

  ;; Square movement
  ;; X
  (cond ((input-values-right p1-input-state)
	 (vec2-x-set! sq-position (+ (vec2-x sq-position)
				     (* 300.0 delta-t))))
	((input-values-left p1-input-state)
	 (vec2-x-set! sq-position (- (vec2-x sq-position)
				     (* 300.0 delta-t)))))
  ;; Y
  (cond ((input-values-down p1-input-state)
	 (vec2-y-set! sq-position (+ (vec2-y sq-position)
				     (* 300.0 delta-t))))
	((input-values-up p1-input-state)
	 (vec2-y-set! sq-position (- (vec2-y sq-position)
				     (* 300.0 delta-t)))))
  
  
  ;; FPS display
  (if (>= (- (sdl2:get-ticks) fps-last-prompt-time) fps-prompt-delay-interval)
      (begin
	(set! fps-last-prompt-time (sdl2:get-ticks))
	(format #t "FPS: ~a, deltaT: ~as\n"
		(if (zero? delta-t) "inf" (/ 1.0 delta-t))
		delta-t))))

;;; Draw func
(define (draw)
  (gl:Clear gl:COLOR_BUFFER_BIT)

  (gl:PushMatrix)
  (gl:Translatef (vec2-x sq-position)
		 (vec2-y sq-position)
		 0.0)
  (gl:Rotatef rotation 0.0 0.0 1.0)
  (gl:Scalef sq-size sq-size 1.0)
  ;; Draw quad
  (gl:Begin gl:QUADS)
  (gl:Color3f 1.0 0.0 0.0)
  (gl:Vertex2f -0.5 -0.5)
  (gl:Color3f 0.0 1.0 0.0)
  (gl:Vertex2f 0.5 -0.5)
  (gl:Color3f 0.0 0.0 1.0)
  (gl:Vertex2f 0.5 0.5)
  (gl:Color3f 1.0 1.0 1.0)
  (gl:Vertex2f -0.5 0.5)
  (gl:End)
  (gl:PopMatrix)
  
  (sdl2:gl-swap-window! window))


(define main-loop
  (lambda ()
    ;; Initialize SDL2
    (sdl2:set-main-ready!)
    (sdl2:init! '(video joystick))
    ;; Create SDL2 window
    (set! window (sdl2:create-window! "SDL2 Scheme"
                                      'centered 'centered
                                      viewport-width viewport-height
                                      '(shown opengl)))
    ;; Create OpenGL context
    (set! gl-context (sdl2:gl-create-context! window))
    (sdl2:gl-make-current! window gl-context)
    
    ;; Initialization
    (init)
    (load-content)

    ;; Actual game loop
    (do-while running
	      ;; Handle SDL2 events
	      (let ((event (sdl2:make-event)))
		(do-while (sdl2:poll-event! event)
			  (case (sdl2:event-type event)
			    
			    ('quit (set! running #f))
			    
			    ('key-down
			     (case (sdl2:keyboard-event-scancode event)
			       ('escape (set! running #f))

			       ('up (input-values-up-set! p1-input-state #t))
			       ('down (input-values-down-set! p1-input-state #t))
			       ('left (input-values-left-set! p1-input-state #t))
			       ('right (input-values-right-set! p1-input-state #t))))
			     
			    ('key-up
			     (case (sdl2:keyboard-event-scancode event)
			       ('up (input-values-up-set! p1-input-state #f))
			       ('down (input-values-down-set! p1-input-state #f))
			       ('left (input-values-left-set! p1-input-state #f))
			       ('right (input-values-right-set! p1-input-state #f))))
					
			    )))
	      ;; Update funcall.
	      ;; Notice DeltaTime calculation
	      (let ((current-time (sdl2:get-ticks)))
		(update (/ (- current-time last-time) 1000.0))
		(set! last-time current-time))
	      ;; Draw funcall
	      (draw))
    ;; Closure
    (unload-content)
    (sdl2:gl-delete-context! gl-context)
    (sdl2:destroy-window! window)
    (sdl2:quit!)))

;; Call main loop func
(main-loop)
