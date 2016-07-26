"A project-specific .virmc file for C++ development
"This was created for my MTRN2500 code
"

set tabstop=4
set softtabstop=4
set shiftwidth=4
set noexpandtab

set colorcolumn=110
highlight ColorColumn ctermbg=darkgray

augroup project
	autocmd!
	autocmd BufRead,BufNewFile *.h,*.c set filetype=c.doxygen
augroup END

let &path.="src/include,/usr/include/AL,"


