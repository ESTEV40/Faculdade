const express = require('express');
const path = require('path');
const conn = require('./Data/db'); // Ajustando o caminho para o arquivo de configuração do banco de dados

const app = express();

app.use(express.urlencoded({ extended: true }));
app.use(express.json());

// Configuração do EJS
app.set('view engine', 'ejs');
app.set('views', path.join(__dirname, 'views'));

// Tornar a conexão acessível para os arquivos de rotas
app.use((req, res, next) => {
  req.conn = conn;
  next();
});

// Configurar rotas
const produtoRoutes = require('./routes/produto');
const categoriaRoutes = require('./routes/categoria');
const pessoaComandaRoutes = require('./routes/pessoaComanda');
const pedidoRoutes = require('./routes/pedido');
const loginRoutes = require('./routes/login');
const indexRoutes = require('./routes/index');

app.use('/', indexRoutes);
app.use('/produto', produtoRoutes);
app.use('/categoria', categoriaRoutes);
app.use('/pessoa_comanda', pessoaComandaRoutes);
app.use('/pedido', pedidoRoutes);
app.use('/login', loginRoutes);

// Configurar pasta pública
app.use(express.static(path.join(__dirname, 'public')));

// Iniciar o servidor
const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Servidor rodando em http://localhost:${PORT}`);
});
