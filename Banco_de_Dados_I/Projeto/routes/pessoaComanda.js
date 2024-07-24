const express = require('express');
const router = express.Router();
const conn = require('../Data/db');

// Rota POST para cadastrar uma nova pessoa na comanda com data de início
router.post('/cadastrar', (req, res) => {
  const { Nome_PessoaComanda, CPF, Mesa } = req.body;
  const conn = req.conn; // Obter a conexão do objeto req

  // Verificar se o cliente já está cadastrado
  const checkSql = 'SELECT ID_PessoaComanda FROM Pessoa_Comanda WHERE CPF = ?';
  conn.query(checkSql, [CPF], (err, results) => {
    if (err) {
      console.log(err);
      return res.status(500).send("Erro ao verificar cliente.");
    }

    if (results.length > 0) {
      // Cliente já está cadastrado, redirecionar para o dashboard
      return res.redirect('/dashboard_cliente');
    } else {
      // Cliente não está cadastrado, realizar a inserção
      const sql = 'INSERT INTO Pessoa_Comanda (Nome_PessoaComanda, CPF, Mesa, Finalizado, DataInicio) VALUES (?, ?, ?, 0, NOW())';
      conn.query(sql, [Nome_PessoaComanda, CPF, Mesa], (err, results) => {
        if (err) {
          console.log(err);
          return res.status(500).send("Erro ao cadastrar pessoa na comanda.");
        }

        // Redirecionar para o dashboard do cliente após o cadastro
        res.redirect('/dashboard_cliente');
      });
    }
  });
});

// Rota POST para atualizar a mesa em Pessoa_Comanda
router.post('/update_mesa', (req, res) => {
  const { ID, Mesa } = req.body;

  const sql = 'UPDATE Pessoa_Comanda SET Mesa = ? WHERE ID = ?';
  
  conn.query(sql, [Mesa, ID], (err, results) => {
    if (err) {
      console.log(err);
      return res.status(500).send("Erro ao atualizar mesa.");
    }

    res.status(200).send("Mesa atualizada com sucesso.");
  });
});

// Rota POST para finalizar uma Pessoa_Comanda
router.post('/finalizar_comanda', (req, res) => {
  const { ID_PessoaComanda } = req.body;

  const sql = 'UPDATE Pessoa_Comanda SET Finalizado = 1, DataFim = NOW() WHERE ID_PessoaComanda = ?';
  
  conn.query(sql, [ID_PessoaComanda], (err, results) => {
    if (err) {
      console.log(err);
      return res.status(500).send("Erro ao finalizar comanda.");
    }

    res.status(200).send("Comanda finalizada com sucesso.");
  });
});

// Rota GET para acompanhar os pedidos de uma comanda específica
router.get('/acompanhar_pedidos/:ID_PessoaComanda', (req, res) => {
  const { ID_PessoaComanda } = req.params;

  const sql = `
    SELECT 
        Nome_Produto as Produto, 
        Descricao_Produto as Descricao, 
        (Valor_Produto - Desconto_Produto) as Subtotal, 
        SUM(Valor_Produto - Desconto_Produto) as Total
    FROM 
        Produto
    INNER JOIN 
        Pedido ON Pedido.ID_Produto = Produto.ID_Produto
    INNER JOIN 
        Pessoa_Comanda ON Pedido.ID_PessoaComanda = Pessoa_Comanda.ID_PessoaComanda
    WHERE
        Pessoa_Comanda.ID_PessoaComanda = ?
    GROUP BY 
        Nome_Produto, 
        Descricao_Produto
    WITH ROLLUP`;

  conn.query(sql, [ID_PessoaComanda], (err, results) => {
    if (err) {
      console.log(err);
      return res.status(500).send("Erro ao acompanhar pedidos.");
    }

    res.json(results);
  });
});

module.exports = router;
