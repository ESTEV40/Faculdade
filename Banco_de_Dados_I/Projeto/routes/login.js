const express = require('express');
const router = express.Router();


// Rota de login do funcionário
router.post('/login', (req, res) => {
  const { Email_Login, Password } = req.body;
  const conn = req.conn;

  const sql = 'SELECT * FROM Funcionario WHERE Email_Login = ?';
  conn.query(sql, [Email_Login], (err, results) => {
    if (err) {
      console.log(err);
      return res.status(500).send("Erro ao verificar login.");
    }

    if (results.length > 0) {
      const user = results[0];
      bcrypt.compare(Password, user.Password, (err, match) => {
        if (err) {
          console.log(err);
          return res.status(500).send("Erro ao verificar login.");
        }

        if (match) {
          res.redirect('/dashboard_funcionario');
        } else {
          res.status(401).send("Email ou senha incorretos.");
        }
      });
    } else {
      res.status(401).send("Email ou senha incorretos.");
    }
  });
});

// Rota para a página de cadastro do funcionário
router.get('/cadastro_funcionario', (req, res) => {
  res.render('cadastro_funcionario');
});

// Rota para cadastrar um novo funcionário
router.post('/cadastro_funcionario', (req, res) => {
  const { Nome_Funcionario, CPF, Email_Login, Password } = req.body;
  const conn = req.conn;

  bcrypt.hash(Password, 10, (err, hashedPassword) => {
    if (err) {
      console.log(err);
      return res.status(500).send("Erro ao cadastrar funcionário.");
    }

    const sql = 'INSERT INTO Funcionario (Nome_Funcionario, CPF, Email_Login, Password) VALUES (?, ?, ?, ?)';
    conn.query(sql, [Nome_Funcionario, CPF, Email_Login, hashedPassword], (err, results) => {
      if (err) {
        console.log(err);
        return res.status(500).send("Erro ao cadastrar funcionário.");
      }

      res.redirect('/login_funcionario');
    });
  });
});

module.exports = router;
