<h1>Minishell</h1>

	- [ ]  si un meta charcheter il doit etre afficher seulement s'il est dans des quotes (dans les double quote faut gerer les $ ` \$ \' \" \\ All other \ characters are literal (not special)) (dans les simple quotes tout les meta character sont desactiver / du coup il faut reactiver le $)(https://www.tutorialspoint.com/unix/unix-quoting-mechanisms.htm)

Tester les fonctions custom et rajouter les secu au cas ou il y a des erreurs
New parsing: verfier si '' ou ""

- creer une fonction pour modifier la valeur d'un noeud avec le nom du noeud et la nouvelle valeur
- cmd_env(char **cmd_tab_exec);
- cmd_unset(char **cmd_tab_exec);
- cmd tab exec = nom de commande/ option / arg ...
- quand tu as un erreur de parsing: mettre $? a deux dans l'env;
- si $puis de la merde ne pas traduire et rappele le prompt $shit
- si $ puis une variable global: me la traduire
- rajouer le $? dans l'env (initialiser a 0)!! attention ne pas le print si cmd env
- dans parsing theo, mettre g_return_value dans le $? dans l'env
- exit print "exit\n" 
- ne pas taduir le nom du here doc a droite !! il peut ne pas exister
