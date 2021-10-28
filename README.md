# Programa para controle de estoque
Programa para realizar controle de estoque, feito em C++ utilizando banco de dados SQL (MYSQL) e QT como interface gráfica.

Este é o primeiro projeto que criei utilizando interface gráfica e banco de dados. Minha principal motivação é a pratica e o aprofundamento dos conhecimentos obtidos através de estudos e pesquisas.

******

## Janela de Login

</a><img src = "https://i.imgur.com/ZzrG5ss.png" alt="Janela de Login."></a>


A janela de login controla o acesso ao programa, para garantir que pessoas sem autorização não possam alterar os dados registrados. Ainda não foi implementada uma tela para registro de usuários, sendo necessário a inserção manual de novos usuários através do Banco de Dados.

O usuário padrão do sistema é o 'root'. Para realizar o login é preciso informar o usuario 'root' e a senha 'adminroot9'.
 
 ******

## Janela Principal

</a><img src = "https://i.imgur.com/JnPcAjR.png" alt="Janela Principal do Programa."></a>

Ao realizar login, a janela estoque será apresentada, carregando inicialmente todos os produtos registrados anteriormente que estão gravados no Banco de Dados.

O campo de busca por código é utilizado para obter a busca precisa de um determinado produto. O código de produto é único, não sendo permitido a repetição de um código já registrado.

O campo de busca por marca é utilizado quando deseja-se obter uma lista de produtos que ao pesquisar, apresentará uma tabela com todos os produtos que compartilham da mesma marca.

</a><img src = "https://i.imgur.com/rWygMC4.png" alt="Janela Principal com busca realizada por marca."></a>

Para mostrar novamente todos os produtos registrados, o botão 'recarregar' deve ser pressionado. 

</a><img src = "https://i.imgur.com/AB0Z7lt.png" alt="Botão Refresh"></a>

Quando a alteração de algum produto é necessária, é preciso 'carregar' o produto, clicando duas vezes no seu respectivo campo de código ou nome na tabela a direita. Quando o carregamento das informações for realizado, basta inserir a informação no campo desejado e clicar no botão atualizar, adicionar ou remover. Após a alteração, a tabela e as informações serão atualizadas.

******

## Janela de inserção

Para registrar um novo produto, o botão de inserir, na Janela Estoque, deve ser pressionado. 

Então uma janela de inserção será apresentada ao usuário.

</a><img src = "https://i.imgur.com/D32Bniq.png" alt="Janela Inserção de Produto."></a>

Todos os dados devem ser devidamente preenchidos. Os campos de Codigo, Valor, Custo e Quantidade, não permitem que o usuário digite caracteres não numéricos, para a prevenção de possiveis erros.
Qualquer campo em branco, cancela a inserção do produto, mesmo que seja confirmada a sua inserção, sendo obrigatório o preenchimento de todos os campos.

Não é possível inserir um código de um produto já registrado, igualmente com o campo de nome, mostrando uma tela de Alerta para o usuário.

</a><img src = "https://i.imgur.com/eQ3Wglg.png" alt="Mensagem de erro: Código Duplicado."></a>

******

## Janela de Remoção

Para remover um produto, o botão Remover, na Janela Estoque, deve ser pressionado.

Então uma janela de remoção será apresentada ao usuário.

</a><img src = "https://i.imgur.com/vRG9dQO.png" alt="Janela Remoção de Produto."></a>

Para realizar a exclusão de um produto, é preciso digitar o código do produto no campo 'codigo'. Clicando no botão 'pesquisa', todas as informações do produto serão carregadas. Necessitando apenas clicar no botão remover.

Para cada inserção e exclusão de produto realizada, é necessário que o botão atualizar seja pressionado.

*******

## Final

Gostaria de agradecer a todos os meus professores da PUC Goiás que me ensinam e me incentivam diariamente.

Por: Lucas Augusto de Souza.

Cursando o 4º período de Ciência da Computação na PUC Goiás.

</a><img src = "https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white"></a>