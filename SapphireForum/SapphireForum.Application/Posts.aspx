<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Posts.aspx.cs" Inherits="SapphireForum.Application.Posts" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">

    <style type="text/css">
        .posts-list {
            list-style: none;
        }

            .posts-list > li {
                margin: 10px auto;
            }

        .posts-comments-count {
            font-size: 40px;
            line-height: 40px;
            padding: 10px;
            margin: 10px;
            background-color: #0088CC;
            border: 1px solid #027bb7;
            border-radius: 5px;
        }
            .posts-comments-count div {
                font-size: 10px;
                line-height: 12px;
            }

        #DataPagerPosts {
            display: block;
            margin-top: 20px;
            text-align: center;
        }

        .blue {
            color: #0088CC;
        }
    </style>

    <h2><asp:Literal ID="AllPostsHeading" runat="server" Text="All posts" /></h2>
    <asp:ListView ID="lvPosts" runat="server" ItemType="SapphireForum.Application.Models.PostDTO" 
        SelectMethod="lvPosts_GetData">
        <ItemTemplate>
            <li>
                <div class="pull-left text-center posts-comments-count">
                    <%#: Item.CommentsCount %><div>comments</div>
                </div>
                <div>
                    <h3><a href="Post.aspx?id=<%#: Item.Id %>"><%#: Item.Title %></a></h3>
                    <div>
                        <p>
                            asked on: <span class="blue"><%#: Item.PostDate.ToString() %></span>
                            in <a class="btn btn-mini" href="Posts.aspx?category=<%#: Item.Category.Name %>"><i class="icon-list"></i> <%#: Item.Category.Name %></a>
                            by <a class="btn btn-mini" href="Posts.aspx?user=<%#: Item.User.UserName %>"><i class="icon-user"></i> <%# Item.User.UserName %></a>
                        </p>

                        <ul class="inline">
                            <asp:Repeater runat="server" DataSource="<%# Item.Tags %>" 
                                ItemType="SapphireForum.Application.Models.Tag">
                                <ItemTemplate>
                                    <li><a class="btn btn-mini" href="Posts.aspx?tag=<%#: Item.Text %>"><i class="icon-tag"></i> <%#: Item.Text %></a></li>
                                </ItemTemplate>
                            </asp:Repeater>
                        </ul>
                    </div>
                </div>
            </li>
        </ItemTemplate>
        <EmptyDataTemplate>
            <div class="alert alert-error">There are no posts matching the criterias.</div>
        </EmptyDataTemplate>
        <ItemSeparatorTemplate>
            <hr style="clear: both;" />
        </ItemSeparatorTemplate>
        <LayoutTemplate>
            <ul class="posts-list">
                <asp:PlaceHolder ID="itemPlaceholder" runat="server" />
                <asp:DataPager ID="DataPagerPosts" ClientIDMode="Static" runat="server" PagedControlID="lvPosts"
                    PageSize="6">
                    <Fields>
                        <asp:NextPreviousPagerField ButtonCssClass="btn" ShowFirstPageButton="True" ShowNextPageButton="False" />
                        <asp:NumericPagerField />
                        <asp:NextPreviousPagerField ButtonCssClass="btn" ShowLastPageButton="True" ShowPreviousPageButton="False" />
                    </Fields>
                </asp:DataPager>
            </ul>
        </LayoutTemplate>
    </asp:ListView>

</asp:Content>
