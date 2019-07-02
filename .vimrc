set nocompatible              " be iMproved, required
filetype off                  " required
" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')
" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'
Plugin 'scrooloose/nerdcommenter'
Plugin 'fatih/vim-go'
Plugin 'Valloric/YouCompleteMe'
Plugin 'Lokaltog/vim-powerline'
Plugin 'tamlok/detorte'
Plugin 'tomasr/molokai'
Plugin 'scrooloose/nerdtree'
Plugin 'majutsushi/tagbar'
Plugin 'octol/vim-cpp-enhanced-highlight'
Plugin 'fholgado/minibufexpl.vim'
Plugin 'dyng/ctrlsf.vim'
Plugin 'derekwyatt/vim-fswitch'
Plugin 'Yggdroot/LeaderF'
"Plugin 'vim-airline/vim-airline'

" The following are examples of different formats supported.
" Keep Plugin commands between vundle#begin/end.
" plugin on GitHub repo
" Plugin 'tpope/vim-fugitive'
" plugin from http://vim-scripts.org/vim/scripts.html
" Plugin 'L9'
" Git plugin not hosted on GitHub
"Plugin 'git://git.wincent.com/command-t.git'
" git repos on your local machine (i.e. when working on your own plugin)
"Plugin 'file:///home/gmarik/path/to/plugin'
" The sparkup vim script is in a subdirectory of this repo called vim.
" Pass the path to set the runtimepath properly.
"Plugin 'rstacruz/sparkup', {'rtp': 'vim/'}
" Install L9 and avoid a Naming conflict if you've already installed a
" different version somewhere else.
" Plugin 'ascenator/L9', {'name': 'newL9'}
" All of your Plugins must be added before the following line
call vundle#end()            " required
filetype plugin indent on    " required

" To ignore plugin indent changes, instead use:
filetype plugin on

" leader key                       
let g:mapleader=";"

" powerline                               
let g:Powerline_colorscheme='solarized256'
" nerdcommenter optional config
let g:NERDCustomDelimiters = { 'c': { 'left': '//','right': '' } }
"
" other config
set laststatus=2
set t_Co=256

set ruler
set cursorline
" highlight CursorLine   cterm=NONE ctermbg=blue ctermfg=black guibg=NONE guifg=NONE
"hi CursorLine   cterm=NONE ctermbg=darkred ctermfg=white guibg=darkred guifg=white
set cursorcolumn
"highlight CursorColumn cterm=NONE ctermbg=blue ctermfg=green guibg=NONE guifg=NONE
set foldmethod=syntax
set nofoldenable

" nerdtree config
nmap <F3> :NERDTreeToggle<CR>
"autocmd vimenter * NERDTree
let NERDTreeWinSize=32
"let NERDTreeWinPos="right"
let NERDTreeMinimalUI=1
let NERDTreeAutoDeleteBuffer=1

"minibuffer explore
map <Leader>bl :MBEToggle<cr>
nmap <Leader>1 :b1<cr>
nmap <Leader>2 :b2<cr>
nmap <Leader>3 :b3<cr>
nmap <Leader>4 :b4<cr>
nmap <Leader>5 :b5<cr>
nmap <Leader>6 :b6<cr>
nmap <Leader>7 :b7<cr>
nmap <Leader>8 :b8<cr>
nmap <Leader>9 :b9<cr>

" tagbar
nmap <F8> :TagbarToggle<CR>
colorscheme molokai
let g:detorte_theme_mode = 'dark'
"set background=dark

"cpp syntax highlight
syntax keyword cppSTLtype initializer_list
let g:cpp_class_scope_highlight = 1
let g:cpp_member_variable_highlight = 1
let g:cpp_concepts_highlight = 1
let g:cpp_experimental_simple_template_highlight = 1

"search in project
nnoremap <Leader>sp :CtrlSF<CR>

" *.cpp 和 *.h 间切换
nmap <silent> <Leader>sw :FSHere<cr>

" 文件模糊查找
nnoremap <silent><leader>f :LeaderfFile<cr>
let g:Lf_WildIgnore = {
            \ 'dir': ['.svn','.git','.hg','.vscode','.wine','.deepinwine','.oh-my-zsh'],
            \ 'file': ['*.sw?','~$*','*.bak','*.exe','*.o','*.so','*.py[co]']
            \}
let g:Lf_UseCache = 0

" golang config
let g:go_fmt_command = "goimports"

" 关闭发现ycm config提示
let g:ycm_confirm_extra_conf = 0
"let g:ycm_global_ycm_extra_conf = '/root/.vim/bundle/YouCompleteMe/.ycm_extra_conf.py'
let g:ycm_global_ycm_extra_conf = '/root/.vim/bundle/YouCompleteMe/third_party/ycmd/cpp/ycm/conf.py'
" 跳转至定义或声明
nnoremap <silent><leader>j :YcmCompleter GoToDefinitionElseDeclaration<cr>
"补全后自动关闭预览窗口
let g:ycm_autoclose_preview_window_after_completion = 1
"
" Brief help
" :PluginList       - lists configured plugins
" :PluginInstall    - installs plugins; append `!` to update or just
" :PluginUpdate
" :PluginSearch foo - searches for foo; append `!` to refresh local cache
" :PluginClean      - confirms removal of unused plugins; append `!` to
" auto-approve removal
"
" see :h vundle for more details or wiki for FAQ
" Put your non-Plugin stuff after this line
