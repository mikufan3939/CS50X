import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


def updatePortfolio(username):
    purchases = db.execute("SELECT * FROM purchases WHERE username=?", username)
    symbols = []
    portfolio = []
    for i in purchases:
        if i["symbol"] not in symbols:
            symbols.append(i["symbol"])
            portfolio.append({"symbol": i["symbol"], "shares": 0, "total": 0, "price": i["price"]})
    for i in purchases:
        for j in portfolio:
            if i["symbol"] == j["symbol"] and i["trans"] == "buy":
                j["shares"] = j["shares"]+i["shares"]
                j["total"] = j["total"]+i["total"]
            elif i["symbol"] == j["symbol"] and i["trans"] == "sell":
                j["shares"] = j["shares"]-i["shares"]
                j["total"] = j["total"]-i["total"]
    for i in purchases:
        for j in portfolio:
            if j["shares"] <= 0:
                portfolio.remove(j)
    print("Look Here!")
    print(symbols)
    print(portfolio)
    return portfolio


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    """Show portfolio of stocks"""
    if request.method == "POST":
        addCash = float(request.form.get("cash"))
        currentCash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
        db.execute("UPDATE users SET cash=?", addCash+currentCash[0]["cash"])
        return redirect("/")
    else:
        username = db.execute("SELECT username FROM users WHERE id=?", session["user_id"])
        cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
        portfolio = updatePortfolio(username[0]["username"])
        total = cash[0]["cash"]
        for i in portfolio:
            total = total+i["total"]
        return render_template("index.html", portfolio=portfolio, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = lookup(request.form.get("symbol"))
        cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
        username = db.execute("SELECT username FROM users WHERE id=?", session["user_id"])

        if not symbol:
            return apology("invalid symbol", 400)
        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("invalid number of shares")

        total = shares*symbol["price"]

        if shares < 0:
            return apology("invalid number of shares", 400)
        if cash[0]["cash"] < total:
            return apology("cannot afford the number of shares", 400)

        db.execute("INSERT INTO purchases (username, symbol, shares, total, price, trans, datetime) VALUES (?,?,?,?,?,?,?)",
                   username[0]["username"], symbol["symbol"], shares, total, symbol["price"], "buy", datetime.now())
        db.execute("UPDATE users SET cash=?", cash[0]["cash"]-total)
        updatePortfolio(username[0]["username"])
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    username = db.execute("SELECT username FROM users WHERE id=?", session["user_id"])
    purchases = db.execute("SELECT * FROM purchases WHERE username=?", username[0]["username"])
    return render_template("history.html", purchases=purchases)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = lookup(request.form.get("symbol"))
        if not symbol:
            return apology("invalid symbol", 400)
        return render_template("quoted.html", symbol=symbol)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        usernames = db.execute("SELECT username FROM users")
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if not username:
            return apology("must provide username", 400)
        for user in usernames:
            if username in user['username']:
                return apology("username already exists", 400)
        if not password or not confirmation:
            return apology("must provide password", 400)
        if password != confirmation:
            return apology("passwords must match", 400)
        hashedPassword = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES (?,?)", username, hashedPassword)
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    username = db.execute("SELECT username FROM users WHERE id=?", session["user_id"])
    portfolio = updatePortfolio(username[0]["username"])
    symbols = []
    cash = db.execute("SELECT cash FROM users WHERE username=?", username[0]["username"])
    for i in portfolio:
        symbols.append(i["symbol"])
    if request.method == "POST":
        symbol = request.form.get("symbol")
        share = int(request.form.get("shares"))
        for i in portfolio:
            if i["symbol"] == symbol:
                totalShares = i["shares"]
                price = i["price"]
        total = price*share
        if not symbol:
            return apology("select a valid stock", 400)
        if not any(symbols["symbol"] == symbol for symbols in portfolio):
            return apology("select a valid stock", 400)
        if share < 0:
            return apology("select a valid number", 400)
        if share > totalShares:
            return apology("not enough stocks", 400)
        db.execute("INSERT INTO purchases (username, symbol, shares, total, price, trans, datetime) VALUES (?,?,?,?,?,?,?)",
                   username[0]["username"], symbol, share, total, price, "sell", datetime.now())
        db.execute("UPDATE users SET cash=?", cash[0]["cash"]+total)
        return redirect("/")
    else:
        return render_template("sell.html", symbols=symbols)
