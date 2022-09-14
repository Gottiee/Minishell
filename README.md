<h1>Minishell</h1>


- creer une fonction pour modifier la valeur d'un noeud avec le nom du noeud et la nouvelle valeur
- cmd_env(char **cmd_tab_exec);
- cmd_unset(char **cmd_tab_exec);
- cmd tab exec = nom de commande/ option / arg ...
- quand tu as un erreur de parsing: mettre $? a deux dans l'env;
- rajouer le $? dans l'env (initialiser a 0)!! attention ne pas le print si cmd env
- dans parsing theo, mettre g_return_value dans le $? dans l'env
- exit print "exit\n" 
- si $ puis une variable global: me la traduire
- rajouter la trad de $? dans txt_trad
- Tester les fonctions custom et rajouter les secu au cas ou il y a des erreurs
- si $puis de la merde ne pas traduire et rappele le prompt $shit 
(si $dfgdfg ca n'affiche rien mais ne pas rappeler le prompt car tu peut faire "echo $gfdgdfg test" et a va print "test")
- ne pas taduir le nom du here doc a droite !! il peut ne pas exister
(il n'est deja jamais traduit)

- export/unset sont run dans un child du coup ca save pas l'add ou le remove de la var

- [ ]  si un meta charcheter il doit etre afficher seulement s'il est dans des quotes (dans les double quote faut gerer les $ ` \$ \' \" \\ All other \ characters are literal (not special)) (dans les simple quotes tout les meta character sont desactiver / du coup il faut reactiver le $)(https://www.tutorialspoint.com/unix/unix-quoting-mechanisms.htm)
- traduire tout sauf le heredoc
- faire l'erreur de l'export clean