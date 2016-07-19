;;;; A Lisp + SDL2 + OpenGL example.

;;;; Most of the code here was borrowed from cl-sdl2 examples,
;;;; however I simplified it and stripped it down of bloat so
;;;; it still remains simple, but is still a template.

;;;; To run this, install Quicklisp on your REPL and load
;;;; SDL2 with (ql:quickload "sdl2").

;;;; It is also unecessary to say that you need to install SDL2
;;;; on your system so this could work.

(require :sdl2)
(require :cl-opengl)

(defun main ()
  (sdl2:with-init (:everything)
    (format t "SDL v~D.~D.~D~%"
            sdl2-ffi:+sdl-major-version+
            sdl2-ffi:+sdl-minor-version+
            sdl2-ffi:+sdl-patchlevel+)
    (finish-output)

    (sdl2:with-window (win :flags '(:shown :opengl))
        (sdl2:with-gl-context (gl-context win)
          ;; Window setup
          (sdl2:gl-make-current win gl-context)
          (gl:viewport 0 0 800 600)
          (gl:matrix-mode :projection)
          (gl:ortho -2 2 -2 2 -2 2)
          (gl:matrix-mode :modelview)
          (gl:load-identity)
          (gl:clear-color 0.0 0.0 0.0 1.0)
          (gl:clear :color-buffer)

          ;; Main loop
          (sdl2:with-event-loop (:method :poll)
            (:keydown (:keysym keysym)
                (let ((scancode (sdl2:scancode-value keysym))
                      (sym (sdl2:sym-value keysym))
                      (mod-value (sdl2:mod-value keysym)))
                  (cond
                    ((sdl2:scancode= scancode :scancode-s) (sdl2:show-cursor))
                    ((sdl2:scancode= scancode :scancode-h) (sdl2:hide-cursor)))
                  ))
            ;; :keyup, etc

            (:idle ()
                (gl:clear :color-buffer)
                (gl:begin :triangles)
                (gl:color 1.0 0.0 0.0)
                (gl:vertex 0.0 1.0)
                (gl:color 0.0 1.0 0.0)
                (gl:vertex -1.0 -1.0)
                (gl:color 0.0 0.0 1.0)
                (gl:vertex 1.0 -1.0)
                (gl:end)
                (gl:flush)
                (sdl2:gl-swap-window win))

            (:quit () t))))))

