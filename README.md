FSMDriver
=========

Inserir descrição do projeto.

Compilação
----------

Arquivos binários devem ser gerados no diretório _bin_. A compilação é simples:

    cd build
    cmake ..
    make

Execução
--------

Descerver a execução:

    torcs &
    ./bin/FSMDrive

Desenvolvimento
-----------

A ferramenta Git é ideal para desenvolvimento em grupo. Basta ter cuidados para
não alterar diretamente o _master_ (geralmente, via _[branching](http://git-scm.com/book/en/Git-Branching-What-a-Branch-Is).
Um exemplo simples:

    git checkout master
    git pull
    git branch MinhasAlteracoes
    git checkout MinhasAlteracoes
    # alterações + commit
    git checkout master
    git merge MinhasAlteracoes
    git push