<h1>Minishell</h1>


 - [ ] pipex(char **env, char *str)eliot
	<ul>
		<li>split les commandes par les pipes</li>
		<li>fork pour chaque </li>
		<li>split par les espaces</li>
		<li>parsing: '<<' / '<' / '>' / '>>' </li>
			- si pipe mettre la sortie sur le pipe (sortie modifiable apres si > ou >>)
			- si < tcheck dabord le fd puis apres la commande
			- si << doc_here
			- apres avoir effectuer un << ou < regerder la sortie
			- si > crer le fichier / l'ouvrire et faire la commande ecraser les donner du fichier avec O_TRUNC
			- si >> // faire la commande et ecrire a la suite O_APPEND
			- <strong>ATTENTION</strong> si pipe apres > ou >> ne pas rediriger dans le pipe mets dans le fichier
	</ul>
- [X] int	cmd_type(char *arg); ->return 1 si execve et 0 une commande qu'on a codee. Theo
- [ ] promp theo 
	- [X] recuperer l'entree utilisateur et la clean
	- [X] l'envoyer au parsing
	- [X] rajouter un historique des commandes(dnas le prompt)
	- [X] pourvoir reprendre les commandes d'avant(fleche du haut)
- [ ] parsing: theo
	- [X]  si presence de \ ou de "' non fermer ou de ; marquer error syntax;
	- [ ]  si un meta charcheter il doit etre afficher seulement s'il est dans des quotes (dans les double quote faut gerer les $ ` \$ \' \" \\ All other \ characters are literal (not special)) (dans les simple quotes tout les meta character sont desactiver / du coup il faut reactiver le $)(https://www.tutorialspoint.com/unix/unix-quoting-mechanisms.htm)
	<strong>ATTENTION</strong> si "" le dollar rester une variable
	- [ ]  si detection de =
		- [X] verifier qu'il soit pas dans des quotes</li>
			- [ ] si l'est envoie a pipex sans les quotes
		- [ ] si l'est pas:</li>
			- [ ] regarder si l'argument passer avant est entre double quote si oui, envoyer a pipex sans les quotes.
			- [ ] verifier si apres le egal il y a un caratere autre que espace envoyer ce qu'il y apres les espaces a pipex
				- [X] pas d'espace entre le nom de la variable et l'egal sinon pipex;
		- [ ] si tout vas bien</li>$
			- [ ] tchequer si la variable existe dans les variables d'environnement et la modifier si le cas present et ne pas la creer
				- [X] sinon ajouter la variable dans une litse chaines de void etoiles; creer la stucture static et mettre
			- [ ] checker si la declaration de var est la derniere cmd de la ligne ("ok=5 | ls" >> ne fait pas la declaration de var // "ls | ok=5" fait la declaration de var mais pas le ls)
			- [ ] <strong>ATTENTION</strong> stocker les chiffres dans un long long;(a faire lors de la convertion)
			- [X] retourner un echo vide
			- [X] supprimer les quotes non necessaire ex (a="test"de'p'    ->    a=testdep)
	- [ ] prendre en compte les operations (ex oui=$((4+5))) + calcul dans export
	- [ ] si ok=$(ls) alors ok prend le resultat de la commande ls
	- [X] verifier que le nom de la variable est constituer seulement de lettres, chiffre underscore mais nest pas egal a "_" ou qu'il n'y ai pas que des chiffres dans le nom de la var
	- [ ] pour les cmd ($(ls)) dans les decl de var, fork et rediriger la sortie standart et que j'appelle pipex 
		- si erreur de syntaxe, si pipex renvoie newline, pour (ok=$(ok >))renvoyer bash: command substitution: line 3: syntax error near unexpected token `)' bash: command substitution: line 3: `ok >)'
	- [X]  creer une recherche par le nom pour trouver la structure dans la liste chainee (fonction dans les deux listes) :theo
	- [ ]  gerer pour le here doc
	- [ ] traduire les variable locale et env quand elle existe
- [X] initialser liste chaine des variables d'env; theo
- [ ] gerer les signaux avec les controls.
- [ ] coder echo:
				- le tiret enleve le \n a la fin du echo
- [ ] coder cd:
- [ ] coder export and unset:
	- modifier la lister chainee 
	- modifier les variables d'environnement 
<strong>ATTENTION</strong> revoyer dans la variable global la valeur de sortie: int	return_value;
<strong>ATTENTION</strong> CREEER UN FREE ALL DANS LE MAIN POUR TJ FREE LES MALLOCS
- [ ] makefile
- [ ] clean les .h

- [ ] ON DOIT GERER CA ? \ exp: "<     \|" essaye d'ouvire | 

bon c'est la merde ! on a plein de nouvelle commande a la con a gerer: 

$: <<test"" cat
$USER
> test
$USER

$: <<test cat
$USER
test
eedy

export ls="ls -la"
$ls
export a=$ls
export"" b=$ls
echo $b
export c=ls -la
export c=ls =la
export c=ls d=oui
env
export c=ls -la
echo $ls
exp"o"rt c=$ls
<< test << ok > | << fle



Rajouter la sauvegarde de l'env avec un fichier txt
Tester les fonctions custom et rajouter les secu au cas ou il y a des erreurs
